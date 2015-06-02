#!/bin/bash

# WRITTEN BY GGILABERT https://github.com/ggila/push_swap

if [ $# -eq 0 ]
then
	./push_swap `ruby -e "puts (0...20).to_a.shuffle.join(' ')"`


elif [ $1 = "-h" ]
then
	echo "./test [-tv] [nb_arg]"


elif [ $# -eq 1 ]
then
	cmd=`ruby -e "puts (0...$1).to_a.shuffle.join(' ')"`
	./push_swap $cmd


elif [ $# -eq 2 ] && [ $1 = "test" ] && [ $2 = all ]
then
	i=1
	min50=0
	min100=0
	min1000=0
	min2000=0
	while [ "true" ]
	do
		echo -ne "$i\t4 : "
		cmd=`ruby -e "puts (0...4).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -ne "\t5 : "
		cmd=`ruby -e "puts (0...5).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -ne "\t6 : "
		cmd=`ruby -e "puts (0...6).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		# echo -ne "\t\t\t\t7 : "
		# cmd=`ruby -e "puts (0...7).to_a.shuffle.join(' ')"`
		# ./push_swap -i $cmd | wc -w |tr -d '\n'
		# echo -ne "\t10 : "
		# cmd=`ruby -e "puts (0...10).to_a.shuffle.join(' ')"`
		# ./push_swap -i $cmd | wc -w |tr -d '\n'
		echo -ne "\t7 : "
		cmd=`ruby -e "puts (0...7).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -ne "\t10 : "
		cmd=`ruby -e "puts (0...10).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t14 : "
		cmd=`ruby -e "puts (0...14).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t15 : "
		cmd=`ruby -e "puts (0...15).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t50 : "
		cmd=`ruby -e "puts (0...50).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t100 : "
		cmd=`ruby -e "puts (0...100).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t500 : "
		cmd=`ruby -e "puts (0...500).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -en "\t1000 : "
		cmd=`ruby -e "puts (0...1000).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w |tr -d '\n'
		echo -ne "\t2000 : "
		cmd=`ruby -e "puts (0...2000).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w
		i=$(( $i + 1 ))
done


elif [ $# -eq 2 ] && [ $1 = "test" ]
then
	i=1
	while [ $i -le 10 ]
	do
		cmd=`ruby -e "puts (0...$2).to_a.shuffle.join(' ')"`
		./push_swap $cmd | wc -w
		i=$(( $i + 1 ))
done


elif [ $# -eq 2 ]
then
	cmd=`ruby -e "puts (0...$2).to_a.shuffle.join(' ')"`
	echo
	echo '         ' $cmd
	echo
	./push_swap $1 $cmd


fi


#if [[ $1 =~ -[^0-9] ]]
#then
#	echo "coucou"
#fi
