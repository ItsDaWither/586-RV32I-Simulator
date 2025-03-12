import os
import subprocess
import glob
import argparse

def run_tests(verbose=False):
    # Find all .mem files in the assembly_tests directory recursively
    mem_files = glob.glob("assembly_tests/**/*.mem", recursive=True)

    if not mem_files:
        print("No .mem files found in the assembly_tests directory.")
        return

    # Iterate through each .mem file
    failing_tests = []
    for mem_file in mem_files:
        if verbose:
            print(f"Running test: {mem_file}")
        # Run the simulator with the .mem file as input
        result = subprocess.run(["./riscv", "verbose", mem_file], capture_output=True, text=True)

        # Parse the output for success or failure
        output = result.stdout
        if "x29: 0x00000001" in output:
            if verbose:
                print(f"{mem_file}: PASSED")
        else:
            print(f"{mem_file}: FAILED")
            failing_tests.append(mem_file)
            if verbose:
                print(f"  Output: {output}") # Print the output to help debug failures

    if not verbose:
        if not failing_tests:
            print("All tests passed!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run assembly tests.")
    parser.add_argument("-v", "--verbose", action="store_true", help="Enable verbose output.")
    args = parser.parse_args()
    run_tests(verbose=args.verbose)
