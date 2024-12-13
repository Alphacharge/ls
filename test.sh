#!/usr/bin/env bats

# Helper function to display test result in color
display_result() {
  local status=$1
  if [ "$status" -eq 0 ]; then
    echo -e "\e[32mOK\e[0m"  # Green for success
  else
    echo -e "\e[31mKO\e[0m"  # Red for failure
  fi
}

# Unified function to run and compare outputs
call_ls() {
  local args="$1"
  local mode="$2"

  case "$mode" in
    0) #STDOUT
		ft_ls_output=$(./ft_ls $args)
		ls_output=$(ls $args)
		;;
  	1) #PIPE
		ft_ls_output=$(./ft_ls | wc -l)
		ls_output=$(ls | wc -l)
		;;
  	2) #REDIRECT
		./ft_ls > ft_ls_output.txt
		ls > ls_output.txt
		ft_ls_output=$(cat ft_ls_output.txt)
		ls_output=$(cat ls_output.txt)
		;;
	esac
  # Compare outputs
  if [ "$ft_ls_output" = "$ls_output" ]; then
#    display_result 0
	return 0
  else
    display_result 1
    #echo -e "Expected:\n$ls_output"
    #echo -e "Got:\n$ft_ls_output"
    return 1
  fi
}

# Suppress BATS error messages
BATS_ERROR_MESSAGE_SUPPRESSION="true"
export BATS_ERROR_MESSAGE_SUPPRESSION

@test "No arguments (STDOUT)" {
call_ls "" 0
}

@test "(-a) (STDOUT)" {
call_ls "-a" 0
}

@test "(-l) (STDOUT)" {
call_ls "-l" 0
}

@test "(-R) (STDOUT)" {
call_ls "-R" 0
}

@test "(-r) (STDOUT)" {
call_ls "-r" 0
}

@test "(-t) (STDOUT)" {
call_ls "-t" 0
}

@test "(-al) (STDOUT)" {
call_ls "-al" 0
}

@test "(-aR) (STDOUT)" {
call_ls "" 0
}

@test "(-ar) (STDOUT)" {
call_ls "" 0
}

@test "(-at) (STDOUT)" {
call_ls "-at" 0
}

@test "(-lR) (STDOUT)" {
call_ls "-lR" 0
}

@test "(-lr) (STDOUT)" {
call_ls "-lr" 0
}

@test "(-lt) (STDOUT)" {
call_ls "-lt" 0
}

@test "(-Rr) (STDOUT)" {
call_ls "-Rr" 0
}

@test "(-Rt) (STDOUT)" {
call_ls "-Rt" 0
}

@test "(-rt) (STDOUT)" {
call_ls "-rt" 0
}

@test "(-alR) (STDOUT)" {
call_ls "-alR" 0
}

@test "(-alr) (STDOUT)" {
call_ls "-alr" 0
}

@test "(-alt) (STDOUT)" {
call_ls "-alt" 0
}

@test "(-aRr) (STDOUT)" {
call_ls "-aRr" 0
}

@test "(-aRt) (STDOUT)" {
call_ls "-aRt" 0
}

@test "(-art) (STDOUT)" {
call_ls "-art" 0
}

@test "(-lRr) (STDOUT)" {
call_ls "-lRr" 0
}

@test "(-lRt) (STDOUT)" {
call_ls "-lRt" 0
}

@test "(-lrt) (STDOUT)" {
call_ls "-lrt" 0
}

@test "(-Rrt) (STDOUT)" {
call_ls "-Rrt" 0
}

@test "(-alRr) (STDOUT)" {
call_ls "-alRr" 0
}

@test "(-alRt) (STDOUT)" {
call_ls "-alRt" 0
}

@test "(-alrt) (STDOUT)" {
call_ls "-alrt" 0
}

@test "(-aRrt) (STDOUT)" {
call_ls "-aRrt" 0
}

@test "(-lRrt) (STDOUT)" {
call_ls "-lRrt" 0
}

@test "(-alRrt) (STDOUT)" {
call_ls "-alRrt" 0
}

@test "(single dir) (STDOUT)" {
call_ls "src" 0
}

@test "(absolut path) (STDOUT)" {
call_ls "$PWD/src" 0
}

@test "No arguments (PIPE)" {
call_ls "" 1
}

@test "(-a) (PIPE)" {
call_ls "-a" 1
}

@test "(-l) (PIPE)" {
call_ls "-l" 1
}

@test "(-R) (PIPE)" {
call_ls "-R" 1
}

@test "(-r) (PIPE)" {
call_ls "-r" 1
}

@test "(-t) (PIPE)" {
call_ls "-t" 1
}

@test "(-al) (PIPE)" {
call_ls "-al" 1
}

@test "(-aR) (PIPE)" {
call_ls "" 1
}

@test "(-ar) (PIPE)" {
call_ls "" 1
}

@test "(-at) (PIPE)" {
call_ls "-at" 1
}

@test "(-lR) (PIPE)" {
call_ls "-lR" 1
}

@test "(-lr) (PIPE)" {
call_ls "-lr" 1
}

@test "(-lt) (PIPE)" {
call_ls "-lt" 1
}

@test "(-Rr) (PIPE)" {
call_ls "-Rr" 1
}

@test "(-Rt) (PIPE)" {
call_ls "-Rt" 1
}

@test "(-rt) (PIPE)" {
call_ls "-rt" 1
}

@test "(-alR) (PIPE)" {
call_ls "-alR" 1
}

@test "(-alr) (PIPE)" {
call_ls "-alr" 1
}

@test "(-alt) (PIPE)" {
call_ls "-alt" 1
}

@test "(-aRr) (PIPE)" {
call_ls "-aRr" 1
}

@test "(-aRt) (PIPE)" {
call_ls "-aRt" 1
}

@test "(-art) (PIPE)" {
call_ls "-art" 1
}

@test "(-lRr) (PIPE)" {
call_ls "-lRr" 1
}

@test "(-lRt) (PIPE)" {
call_ls "-lRt" 1
}

@test "(-lrt) (PIPE)" {
call_ls "-lrt" 1
}

@test "(-Rrt) (PIPE)" {
call_ls "-Rrt" 1
}

@test "(-alRr) (PIPE)" {
call_ls "-alRr" 1
}

@test "(-alRt) (PIPE)" {
call_ls "-alRt" 1
}

@test "(-alrt) (PIPE)" {
call_ls "-alrt" 1
}

@test "(-aRrt) (PIPE)" {
call_ls "-aRrt" 1
}

@test "(-lRrt) (PIPE)" {
call_ls "-lRrt" 1
}

@test "(-alRrt) (PIPE)" {
call_ls "-alRrt" 1
}

@test "(single dir) (PIPE)" {
call_ls "src" 1
}

@test "(absolut path) (PIPE)" {
call_ls "$PWD/src" 1
}

@test "No arguments (REDIRECT)" {
call_ls "" 2
}

@test "(-a) (REDIRECT)" {
call_ls "-a" 2
}

@test "(-l) (REDIRECT)" {
call_ls "-l" 2
}

@test "(-R) (REDIRECT)" {
call_ls "-R" 2
}

@test "(-r) (REDIRECT)" {
call_ls "-r" 2
}

@test "(-t) (REDIRECT)" {
call_ls "-t" 2
}

@test "(-al) (REDIRECT)" {
call_ls "-al" 2
}

@test "(-aR) (REDIRECT)" {
call_ls "" 2
}

@test "(-ar) (REDIRECT)" {
call_ls "" 2
}

@test "(-at) (REDIRECT)" {
call_ls "-at" 2
}

@test "(-lR) (REDIRECT)" {
call_ls "-lR" 2
}

@test "(-lr) (REDIRECT)" {
call_ls "-lr" 2
}

@test "(-lt) (REDIRECT)" {
call_ls "-lt" 2
}

@test "(-Rr) (REDIRECT)" {
call_ls "-Rr" 2
}

@test "(-Rt) (REDIRECT)" {
call_ls "-Rt" 2
}

@test "(-rt) (REDIRECT)" {
call_ls "-rt" 2
}

@test "(-alR) (REDIRECT)" {
call_ls "-alR" 2
}

@test "(-alr) (REDIRECT)" {
call_ls "-alr" 2
}

@test "(-alt) (REDIRECT)" {
call_ls "-alt" 2
}

@test "(-aRr) (REDIRECT)" {
call_ls "-aRr" 2
}

@test "(-aRt) (REDIRECT)" {
call_ls "-aRt" 2
}

@test "(-art) (REDIRECT)" {
call_ls "-art" 2
}

@test "(-lRr) (REDIRECT)" {
call_ls "-lRr" 2
}

@test "(-lRt) (REDIRECT)" {
call_ls "-lRt" 2
}

@test "(-lrt) (REDIRECT)" {
call_ls "-lrt" 2
}

@test "(-Rrt) (REDIRECT)" {
call_ls "-Rrt" 2
}

@test "(-alRr) (REDIRECT)" {
call_ls "-alRr" 2
}

@test "(-alRt) (REDIRECT)" {
call_ls "-alRt" 2
}

@test "(-alrt) (REDIRECT)" {
call_ls "-alrt" 2
}

@test "(-aRrt) (REDIRECT)" {
call_ls "-aRrt" 2
}

@test "(-lRrt) (REDIRECT)" {
call_ls "-lRrt" 2
}

@test "(-alRrt) (REDIRECT)" {
call_ls "-alRrt" 2
}

@test "(single dir) (REDIRECT)" {
call_ls "src" 2
}

@test "(absolut path) (REDIRECT)" {
call_ls "$PWD/src" 2
}