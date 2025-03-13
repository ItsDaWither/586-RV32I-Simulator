import os
import subprocess
import argparse

c_files_dir = "c_tests"
build_dir = "build"

parser = argparse.ArgumentParser(description="Generate .mem files from C files.")
parser.add_argument("-v", "--verbose", action="store_true", help="Enable verbose output.")
args = parser.parse_args()

def run_commands(c_file):
    try:
        base_name = os.path.splitext(c_file)[0]
        assy_file = os.path.join(c_files_dir, base_name.replace(c_files_dir + '/', '') + ".s")
        object_file = os.path.join(c_files_dir, base_name.replace(c_files_dir + '/', '') + ".o")
        out_file = os.path.join(c_files_dir, base_name.replace(c_files_dir + '/', '') + ".out")
        mem_file = os.path.join(c_files_dir, base_name.replace(c_files_dir + '/', '') + ".mem")

        # gcc -Wall -m32 -c test.c -o test.o
        subprocess.run(["/usr/bin/riscv64-elf-gcc", "-Wall", "-march=rv32i", "-mabi=ilp32", "-c", c_file, "-o", object_file], check=True)

        # rv32ld test.o
        subprocess.run(["/usr/bin/riscv64-elf-ld", "-emain", "-melf32lriscv", "-Ttext=0x0",  object_file, "-o", out_file], check=True)

        # riscv64-linux-gnu-objdump -d test.o | ./rv32pp > test.mem
        with open(mem_file, "w") as outfile:
            rv32objdump_process = subprocess.Popen(["/usr/bin/riscv64-linux-gnu-objdump", "-d", out_file], stdout=subprocess.PIPE)
            rv32pp_process = subprocess.Popen(["./rv32pp"], stdin=rv32objdump_process.stdout, stdout=outfile)
            if rv32objdump_process.stdout:
                rv32objdump_process.stdout.close()  # Allow rv32objdump to receive a SIGPIPE if rv32pp exits.
            rv32pp_process.wait()

        if args.verbose:
            print(f"Successfully processed {c_file}")

    except subprocess.CalledProcessError as e:
        print(f"Error processing {c_file}: {e}")
    except FileNotFoundError as e:
        print(f"Error: {e}. Make sure the required tools (gcc, rv32objdump, rv32pp) are in your PATH.")


if __name__ == "__main__":
    for filename in os.listdir(c_files_dir):
        if filename.endswith(".c"):
            c_file = os.path.join(c_files_dir, filename)
            run_commands(c_file)

    if args.verbose:
        print("Finished processing all C files.")
