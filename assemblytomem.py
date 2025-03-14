import os
import subprocess
import argparse

assembly_examples_dir = "assembly_tests"

parser = argparse.ArgumentParser(description="Generate .mem files from assembly files.")
parser.add_argument("-v", "--verbose", action="store_true", help="Enable verbose output.")
args = parser.parse_args()

def run_commands(assembly_file):
    try:
        base_name = os.path.splitext(assembly_file)[0]
        object_file = base_name + ".o"
        output_file = base_name + ".out"
        mem_file = base_name + ".mem"

        # rv32as test.s -o test.o
        subprocess.run(["/usr/bin/riscv64-elf-as", "-fpic", "-march=rv32i", "-mabi=ilp32", assembly_file, "-o", object_file], check=True)

        # rv32ld test.o
        subprocess.run(["/usr/bin/riscv64-elf-ld", "-melf32lriscv", "-Ttext=0x0", object_file, "-o", output_file], check=True)

        # rv32objdump -d | rv32pp > test.mem
        with open(mem_file, "w") as outfile:
            rv32objdump_process_1 = subprocess.Popen(["/usr/bin/riscv64-elf-objdump", "-d", "-j.text", "-j.data", "-j.got.plt", output_file], stdout=subprocess.PIPE)
            rv32objdump_process_2 = subprocess.Popen(["/usr/bin/riscv64-elf-objdump", "-D", "-j.got", output_file], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)

            # Concatenate the outputs of the two objdump processes
            combined_stdout = subprocess.Popen(
                ["cat"],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE
            )
            if rv32objdump_process_1.stdout and rv32objdump_process_2.stdout:
                combined_stdout.stdin.write(rv32objdump_process_1.stdout.read()) # pyright: ignore
                combined_stdout.stdin.write(rv32objdump_process_2.stdout.read()) # pyright: ignore
                rv32objdump_process_1.stdout.close()
                rv32objdump_process_2.stdout.close()
                combined_stdout.stdin.close() # pyright: ignore

            rv32pp_process = subprocess.Popen(["./rv32pp"], stdin=combined_stdout.stdout, stdout=outfile)
            if combined_stdout.stdout:
                combined_stdout.stdout.close()  # Allow cat to receive a SIGPIPE if rv32pp exits.

            rv32pp_process.wait()

        if args.verbose:
            print(f"Successfully processed {assembly_file}")

    except subprocess.CalledProcessError as e:
        print(f"Error processing {assembly_file}: {e}")
    except FileNotFoundError as e:
        print(f"Error: {e}. Make sure the required tools (rv32as, rv32ld, rv32objdump, rv32pp) are in your PATH.")


if __name__ == "__main__":
    for root, _, files in os.walk(assembly_examples_dir):
        for file in files:
            if file.endswith(".s"):
                assembly_file = os.path.join(root, file)
                run_commands(assembly_file)

    if args.verbose:
        print("Finished processing all assembly files.")
