#!/usr/bin/env bats

# Helper function to compare outputs
compare_outputs() {
  expected_output="$1"
  command_output="$2"
  if [ "$expected_output" != "$command_output" ]; then
    echo "Test failed"
    exit 1
  fi
}

@test "Compare stdout of my_ls and ls" {
  # Capture stdout for both commands
  my_ls_output=$(./my_ls)
  ls_output=$(ls)

  compare_outputs "$my_ls_output" "$ls_output"
}

@test "Compare my_ls and ls output redirected to file" {
  # Redirect both outputs to files
  ./my_ls > my_ls_output.txt
  ls > ls_output.txt

  # Compare file contents
  my_ls_file_output=$(cat my_ls_output.txt)
  ls_file_output=$(cat ls_output.txt)

  compare_outputs "$my_ls_file_output" "$ls_file_output"
}

@test "Compare my_ls and ls piped to wc -l" {
  # Compare output when piped to wc -l
  my_ls_piped=$(./my_ls | wc -l)
  ls_piped=$(ls | wc -l)

  compare_outputs "$my_ls_piped" "$ls_piped"
}
