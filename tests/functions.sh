
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
    echo -e "Expected:\n$ls_output"
    echo -e "Got:\n$ft_ls_output"
    return 1
  fi
}

# Suppress BATS error messages
BATS_ERROR_MESSAGE_SUPPRESSION="true"
export BATS_ERROR_MESSAGE_SUPPRESSION