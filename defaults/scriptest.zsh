# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    toaster.zsh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/03 11:19:01 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/15 12:59:19 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# underline
ul="\033[4m"
# bot name color
fst="\033[38;5;88m"
scd="\033[38;5;124m"
trd="\033[38;5;160m"
frt="\033[38;5;196m"
function shuffle_arr()
{
    local shuffled=($my_arr)
    for ((i=1;i<${#my_arr};++i))
    do
        shuffled[$i]=$my_arr[$(( RANDOM % (${#my_arr} - 1)  + 1 ))]
        my_arr=($my_arr[1,$i-1] $my_arr[$i+1,${#my_arr}])
    done
    unset my_arr
    my_arr=($shuffled)
    catch_state_enabled=0
}
function init_usr_input()
{
    loaded=()
    echo -n "Which ${fg[green]}options$reset_color would you like to use: "
    read -rA ops
    echo -n "How much ${fg[green]}players$reset_color would you like to set: "
    read -r nplayers
    if (( nplayers <= 0 || nplayers > 4 ))
    then
        echo "Wrong number, ${fg[red]}terminating$reset_color ..."
        exit 3
    fi
    echo -n "File to write output of ${fg[green]}$ours_prog$reset_color: "
    read -r tmp_fours
    echo -n "File to write output of ${fg[green]}$theirs_prog$reset_color: "
    read -r tmp_ftheirs
    if [[ -n $tmp_fours ]] && [[ -n $tmp_ftheirs ]]
    then
        fours=$tmp_fours
        ftheirs=$tmp_ftheirs
    fi
    echo -n "Champ ${fg[green]}names$reset_color (${fg[cyan]}globing enabled$reset_color): "
    read -r tmp_read_from
    if [[ -n $tmp_read_from ]]
    then
        read_from=$tmp_read_from
        my_arr=($(eval "echo $read_from"))
    fi
    echo -n "Write ${fg[green]}diff$reset_color to: "
    read -r tmp_fdname
    if [[ -n $tmp_fdname ]]
    then
        fdname=$tmp_fdname
    fi
    echo "Run it in ${fg[green]}random$reset_color sequence ? (y/n) (if no, then players will be subtituted ${fg[green]}sequently$reset_color)"
    read -q -s answer
    if [[ $answer == "y" ]]
    then
        shuffle_arr
    fi
}
function check_it()
{
    if [[ $ours_prog_said != "" ]] || [[ $theirs_prog_said != "" ]]
    then
        echo "One of the programs or both are trying to say something !"
        echo "Check file: $ferr"
        echo "$ours_prog_said" >> $ferr
        echo "$theirs_prog_said" >> $ferr
        exit 2
    fi
    differ=$(diff -q $ftheirs $fours)
    if [[ $differ != "" ]]
    then
        echo "${fg[red]}KO!$reset_color"
        diff $ftheirs $fours > $fdname
        echo "Diff is writen to $fdname"
        echo "Would you like to open ${fg[green]}VIM$reset_color ? (y/n)"
        
        echo "Continue ? (y/n)"
        answer="y"
        if [[ $answer == "n" ]]
        then
            exit 0
        fi
    else
        echo " [${fg[green]}OK!$reset_color]"
    fi
}
function catch_state()
{
    echo "$fours" > $fstate
    echo "$ftheirs" >> $fstate
    echo "$read_from" >> $fstate
    echo "$fdname" >> $fstate
    echo "$ops" >> $fstate
}
function players1()
{
    for ((i=si;i<=$arr_size;i++))
    do
        if (( catch_state_enabled )); then catch_state; fi
        echo "$i" >> $fstate
        echo -n "${fg[yellow]}Current files$reset_color "
        echo -n "[${fg[green]}$i$reset_color]/$arr_size: "
        echo -n "${fst}${ul}$my_arr[$i]$reset_color"
        theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" 2>&1 1>$ftheirs)
        ours_prog_said=$(./$ours_prog -log "$my_arr[$i]" 2>&1 1>$fours)
        check_it
    done
    unset i
}
function players2()
{
    for ((i=si;i<=$arr_size;i++))
    do
        for ((j=sj;j<=$arr_size;j++))
        do
            if (( catch_state_enabled )); then catch_state; fi
            echo "$i $j" >> $fstate
            echo -n "${fg[yellow]}Current files$reset_color "
            echo -n "[${fg[green]}$i $j$reset_color]/$arr_size: "
            echo -n "${fst}${ul}$my_arr[$i]$reset_color "
            echo -n "${scd}${ul}$my_arr[$j]$reset_color"
            theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$ftheirs)
            ours_prog_said=$(./$ours_prog -log "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$fours)
            check_it
        done
        sj=1
    done
    unset i j
}
function players3()
{
    for ((i=si;i<=$arr_size;i++))
    do
        for ((j=sj;j<=$arr_size;j++))
        do
            for ((k=sk;k<=$arr_size;k++))
            do
                if (( catch_state_enabled )); then catch_state; fi
                echo "$i $j $k" >> $fstate
                echo -n "${fg[yellow]}Current files$reset_color "
                echo -n "[${fg[green]}$i $j $k$reset_color]/$arr_size: "
                echo -n "${fst}${ul}$my_arr[$i]$reset_color "
                echo -n "${scd}${ul}$my_arr[$j]$reset_color "
                echo -n "${trd}${ul}$my_arr[$k]$reset_color"
                theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$ftheirs)
                ours_prog_said=$(./$ours_prog -log "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$fours)
                check_it
            done
            sk=1
        done
        sj=1
    done
    unset i j k
}
function players4()
{
    for ((i=si;i<=$arr_size;i++))
    do
        for ((j=sj;j<=$arr_size;j++))
        do
            for ((k=sk;k<=$arr_size;k++))
            do
                for ((m=sm;m<=$arr_size;m++))
                do
                    if (( catch_state_enabled )); then catch_state; fi
                    echo "$i $j $k $m" >> $fstate
                    echo -n "${fg[yellow]}Current files$reset_color "
                    echo -n "[${fg[green]}$i $j $k $m$reset_color]/$arr_size: "
                    echo -n "${fst}${ul}$my_arr[$i]$reset_color "
                    echo -n "${scd}${ul}$my_arr[$j]$reset_color "
                    echo -n "${trd}${ul}$my_arr[$k]$reset_color "
                    echo -n "${frt}${ul}$my_arr[$m]$reset_color"
                    theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$ftheirs)
                    ours_prog_said=$(./$ours_prog -log "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$fours)
                    check_it
                done
                sm=1
            done
            sk=1
        done
        sj=1
    done
    unset i j k m
}
function enter_point()
{
    if (( $1 == 1 ))
    then
        players1
    elif (( $1 == 2 ))
    then
        players2
    elif (( $1 == 3 ))
    then
        players3
    elif (( $1 == 4 ))
    then
        players4
    fi
}
ftheirs="/tmp/theirs"
fours="/tmp/ours"
ferr="toaster.err"
fdname="err.diff"
fstate="toaster_state.st"
answer=""
nplayers=1
ours_prog="corewar"
theirs_prog="vm"
ops=""
ours_prog_said=""
theirs_prog_said=""
st=""
integer catch_state_enabled=1
read_from="champs/**/*.cor"
my_arr=($(eval "echo $read_from"))
integer superman_mode=0
stop_at_first_loose="Stop at first loose"
continue_on_loose="Continue on loose"
continue_on_loose_count="Continue on loose with count"
autoload -U colors
colors
# Start here
if [[ -e $fstate ]]
then
    st=$(cat $fstate)
    local mess=(${(f)st})
    fours=$mess[1]
    ftheirs=$mess[2]
    read_from=$mess[3]
    fdname=$mess[4]
    if [[ ${#mess} == 5 ]]
    then
        local ppos=5
        local oppos=0
    else
        local oppos=5
        local ppos=6
    fi
    loaded=(${(s/ /)mess[$ppos]})
    if (( ${#loaded} > 0 && ${#loaded} < 5 ))
    then
        echo "You have a file with previous toaster state."
        echo -n "Would you like to start from last checkpoint"
        echo -n "[${fg[green]}$loaded$reset_color] {np=${fg[green]}${#loaded}$reset_color}"
        echo "{${fg[green]}$fours$reset_color,${fg[green]}$ftheirs$reset_color} (y/n)?"
        read -q -s answer
        if [[ $answer == "y" ]]
        then
            nplayers=${#loaded}
            ops=(${(s/ /)mess[$oppos]})
        else
            loaded=()
            init_usr_input
        fi
    else
        echo "Bad state file, ${fg[red]}terminating$reset_color."
        exit 4
    fi
else
    init_usr_input
fi
si=$(( loaded[1] ? loaded[1] : 1))
sj=$(( loaded[2] ? loaded[2] : 1))
sk=$(( loaded[3] ? loaded[3] : 1))
sm=$(( loaded[4] ? loaded[4] : 1))
nplayers=$(( nplayers ))
arr_size=${#my_arr}
echo "${fg[cyan]}Starting ...${reset_color}"
enter_point $nplayers
echo "You are so lucky ! Everything is ${fg[green]}ok$reset_color !"