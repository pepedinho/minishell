#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' 

MINISHELL_PATH="./minishell"
TEST_COMMANDS="test_commands.txt"
TEMP_DIR="./shell_comparison"
FIFO_PATH="$TEMP_DIR/minishell_fifo"

if [ ! -f "$MINISHELL_PATH" ]; then
	echo -e "${RED} No minishell executable found! Aborting. ${NC}"
	exit
fi

mkdir -p "$TEMP_DIR"

if [ ! -f "$TEST_COMMANDS" ]; then
    cat <<EOL > "$TEST_COMMANDS"
# This file contains the commands to be tested in minishell.
# Add one command per line.
# Lines starting with # are comments and will be ignored. Empty lines will be ignored.

# The file is named test_commands.txt, the script checks for its name so do not rename it.
# Adding 'remove' as the last line will make the script remove it after it is done running. 
# Otherwise, the file will remain in the working directory and can be editted at will between runs.

# The script will NOT remove any files your minishell has created unless specified in the cleanup() function. By default, it will try to rm output1.txt up to output4.txt.

# The script does not handle commands that expect errors to be printed as error messages are typically custom.
# The script will run once you exit vim.

# Example commands:
echo "Hello, World!"
ls -l
pwd
cat Makefile | grep SRC | wc -l
EOL
    vim "$TEST_COMMANDS"
fi

mkfifo "$FIFO_PATH"

cleanup() {
	kill $MINISHELL_PID
	# Add any additional files created by the commands here
	rm -rf output.txt output2.txt output3.txt output4.txt

	rm -rf "$TEMP_DIR"
	exit
}

interrupted() {
	echo -e "${RED} Script interrupted${NC}"
	cleanup
}

$MINISHELL_PATH < "$FIFO_PATH" > "$TEMP_DIR/minishell_output" 2>&1 &
MINISHELL_PID=$!

trap interrupted SIGINT

echo -e " ${YELLOW}


		  _____ _   _        _____ _          _ _    _____                 _                       
		 |_   _| | ( )      / ____| |        | | |  / ____|               | |                      
		   | | | |_|/ ___  | (___ | |__   ___| | | | |  __  ___   ___   __| |_ __ ___   __ _ _ __  
		   | | | __| / __|  \___ \| '_ \ / _ \ | | | | |_ |/ _ \ / _ \ / _| | |_ | _ \ / _| | \_ \ 
		  _| |_| |_  \__ \  ____) | | | |  __/ | | | |__| | (_) | (_) | (_| | | | | | | (_| | | | |
		 |_____|\__| |___/ |_____/|_| |_|\___|_|_|  \_____|\___/ \___/ \__,_|_| |_| |_|\__,_|_| |_| 

 
 ${NC}"

echo -e                        "${YELLOW}                                                                                                                              
________________________________________________________________________________________________________________________________________________________

										 ....... ...............................    ..........................',;,,,'.................'''''',,,,,,;;;;;;::::ccccclllloo
                        ............................... .......................................,;;;;:;,'...........''''''',,,,,,;;;;;:::::cccclllllooo
                        .........................   ............................................',;;;cll:,'.......'''''',,,,,,;;;;;::::ccccccllloooood
                        ...........   ........  .................................................'',,;codxdc'....'''''',,,,,,;;;;;::::cccccllllooooddd
                .................    .....      ....''..............................................';codk00o,''''''',,,,,,,;;;;;:::cccccllllloooddddd
                ............       ...        ...,;;::;;;;,,,,',,,,'''''.........................''',;codkKXXk:'''''',,,,,;;;;;::::cccccllllooooddddxx
                ............     ....       ..',;:::::::::::::::;;;,,,,,'''''....................'',:ccldkOXN0o:;,'',,,,;;;;;:::::cccclllloooooddddxxx
                ............    ......     .',;:::::::ccc:::::::::;;;,,,'''''''..................'',:odxxkO0K0xoc;',,,,;;;;;:::cccccllllloooooddddxxxk
.......        ............   ........    .';::::::::::::::::::::::;;;;,,,''''''''...............',,cdOKK0Okkkkdc,,,,,,,;;;:::cccccllllloooodddddxxxkk
.......        ...........   ........    .';:;:::::::::::::::::::::::;;,,,,,,,,'''''''...........';:cokXNX0kxkkdc;,,,,,,;;;:::ccccclllooooodddddxxxxkk
..........................   ......     ..;::;::::::::::::::::::::::::;;,,,,,,,,,,'''''..........';:cox0NNKkdxO0Od;,,,;;;;:::ccccccllloooodddddxxxxkkk
.......................  .........     ..,;:::::::ccccc::::::::::::::::;;;;;;;;,,,,'''''..........';cod0NWXkolxKXXx:,;;;;::::ccccllllooooodddddxxxkkkk
......................   ........     ..';:::::ccccccccccccc:ccccc:::c::;;;;;;;;;,,,,''''..........,:lx0NWXxlccxKNXk:;;;;:::ccccllllloooodddddxxxxkkkO
......................   ........    ...,:::cccccccccclccccc:ccccccccc::;;;;;;;;;;,,,,,'''.........',:xKNWXkoc:cxKNNk:;:::::ccccclllloooodddddxxxkkkkO
......................  .........   ...';:ccccclllllllcccccccccccccccc:::::::;;;;;;,,,,,'''.........',o0NWNOoc::lkXWNkc::::ccccclllooooodddddxxxxkkkOO
               ....... ..........  ....,:cccccllllllllllllcccccccccc::::cc:::;;;;;;;,,,,'''''........'cOXWN0dc::cd0NWNkc:::cccclllooooodddddxxxxkkkkOO
        .........................  ....,:ccclllllloolloolllccccccccc:::cccc::;;;;;;;,,,,'''''.........:xKWWKkoc:clkXNMXdc::ccccllloooooddddxxxxxkkkOOO
    ...................................,:clllllllooollllllcccccccccc::::cc:::;;;;;;;,,,,''''''........,oKWWXOdlclox0NWWKo::ccccllloooooddddxxxxkkkOOOO
 ...................................''',:cllllllooolllolllccccccccccc::::::::;;;;;;;;,,'''''''........':kNWN0koloxkOXNWXxccccccllloooooddddxxxkkkkOOO0
................. ..................''',;cllllooooooollolllccccccccccc:::c:::::;;;;;;,,''''''..........,dXWWKOxddxOKXNWWOlccccclllooooodddxxxxkkkkOOOO
...............    .................'',,;clllooooooollllllccccc:::cccc:::::::::;;;,,,,,''''''..........':ONWNKkxxdkKXNWWKoccccclllooooddddxxxxkkkkOOO0
................  ................','',;;:cllllloollllllllcccccc::cccccccc::::::;;;;,,,'''''...........';kNWNKOkkkOKNNWWXxc:ccclllooooddddxxxkkkkOOOO0
.................................',;;;;;::clllloollllooollllcccc:::ccccccccccc::::;;,,,'''''...........':kNWWXOkOO0KNWWWXxcccccllloooodddxxxxkkkkOOOO0
................... .............,;;:::::ccllloolloooooooollcccc::::cccccccccc:::::;,,,,''''..........',cONWWXkxO0KXNWWWKoccccclllooodddddxxxkkkkOOOO0
................... .............,;;:::cccllloooooodooddddolllccccc:ccccccccccc::::;;,,,''......'.....,;l0NWWXkdkKXNNWWWKdcllcllllooodddddxxxkkkkOOOO0
..................   ............,;::::ccccllloooodoooddddoooollcc::cccccllllccc:::;;,,,,''.''''.....',ckXNWMNkox0XWWWWN0dclllllllooodddddxxxkkkkOOO00
        ..........   ... .. .....,;::::cccclllloooooooodoooooooollccclccclollccc:::;;,,,,,'''''''...'';lONWWMW0dx0NWWWWKxlllclllllooodddddxxxkkkOOOO00
..      ....... ...  ..     .....,;;:::::ccc:cccllloooooooooooloolccllc:cloolccc:::;;,,,,''''''''..'',:oOXWMWWXkk0NWWWNOdlllclllloooooddddxxxkkkOOOO00
..................    . .   ....',;;::::;;;,'''',,,,;:ccclloollllcccllc::looolccc::;;,'''..........'',:lk0XWMWXkkKNWWNXkocllllllloooooddddxxxxkkkOOO00
..................    .       ..',;;;;:;,,'''..'......''',;:::ccc::colc:;;loocc::;,,''...............',cxOKNWMNOkKNNNXKxlcccllllllooooddddxxxxkkkOOO00
     ..............           ..,,;;;;,;;;::::;;,,,,''.....'',,;;;:lolc:,':cc:;;,'.........'''''''''..';cx0NWMN0k0XKKN0occccclllllooooddddxxxxkkkOOOO0
    ................          ..,,;;,,,;:clllllllllllc:;,,''',,,;;coooc;,.'',,'........',;;;::;;,,,'''',;cd0NMW0xkK00NOoccccclllllooooddddxxxxkkkOOOO0
   ..................         .',,;;,,;:cllooolllc:;;,,'''',;;::cloodol:,...............',,'',,''''''',;;,:oKWWKxxO0kOOoccccccllllloooodddxxxxkkkOOO00
   ...................       ..',;;;;;:cccc:;,,'.,'.......',,;cllooddol:,'...............',...........',,'':OWWXxdkOdxOo:ccccclllllooooddddxxxxkkkOOO0
   .....................     ..',;;::ccc:,'..',,','...''''';::clloooool:,'............',,,,''''''''......'':ONWNkdkOxdko:ccccccllllooooodddxxxxkkkkOOO
    .................        ..',;;::cc:::::::c::;;;,,,,,,,;:cllllooolc:;'...........'',,;;;;;,,''''....''',dXWNkdxkOxxo::ccccclllloooooddddxxxxkkkOOO
     ..............         ...',;:::cccclllllooolcc::;;;;;;:cllloooolc:;'............'',;;;;;,,'.......''',oKNN0xkO0Oxl::cccccclllooooooddddxxxkkkkOO
     ..............         ...',;;:ccccllooooooooolllllc:::ccllloooll:;;'.............'',,,,,,,''''..'''',;o0NWKkkOO0kl::ccccccllllloooooddddxxxkkkOO
     ..............          ..',,;:cclllloooddddddddoolccclloolooolll::;'..............''',,,,,,,'''''''',;o0NNOddkxkOo:::ccccccllllloooodddddxxxkkkk
.  ................          ..'',;:cclllllooddddddoolcccloooooooollllc:;'...............''',,,,,,'''''''',:dKWXxloxlckx::::cccccclllllooooddddxxxxkkk
...................        .....',;:ccllollooooooooollllodddoooooollllc:;'................'''',,,,,,,,''''';dKWKocdd:;dxc::::cccccclllllloooddddxxxxkk
...................        .....',;::cllloooodddddoooooodddoooooooollll:,'................'''''',,,,''''''';xXWOlcxxc;cdl:::::ccccccclllllooooddddxxxk
...................         ....',;;:ccllloodddddooooooddddooooooolllll:,'.................''''''''''''''.';xXNOoxOdolldc;:::::::cccccclllloooddddxxxx
...................          ....',;:ccclloooddooooooooddddooooollllllc:;,...................'''''''''....',dKWX0XO:lodd:;;:::::::ccccccllllooooddddxx
....................  ..     ....',;::ccllllooddddoooooddddooollllllolc:;,'...................'''''''....'',oKWNWWO:;:oo;;;;;::::::ccccccllllloooodddx
....................  ...........',;:::cccllooddddoooooddddoolllllloddlc:;''...................''''.......',oKWWNWO;,co:;;;;;;;;:::::::ccccllllooooddd
.....................   ..........',;::cccclooododdddooooollllllllodxdlcc:,'...........................''.',oKWWWWk;;c:,;;;;;;;;;;::::::cccclllllooodd
..................................',;::cccclloooooddddoolllllllllllooolcc:;,'.........................'''.',oKNWWWk:;;,,,,,,;;;;;;;;;:::::cccclllllooo
..................................',;::ccccclloodddooollllloolc:::cllllcc:,,'.........................','.';dKNNWNd,,,,,,,,,,,;;;;;;;;;:::::cccclllloo
..................................',;:::cccclloooddoollllooolllccccccc:::;'................'''........,,,'';dKXXNXl,,,,,,,,,,,,,,;;;;;;;;:::::ccccllll
..................................',,;::cccclllloddoolloooolllllllccc:;,,,'................'''........','.';oO0KN0:',',,',,,,,,,,,,,;;;;;;;:::::ccccll
..................................',,;::ccccllllooolllolllllllllllllc;'';c:;,................''.......','',:oxk0Kx;','','',,,,,,,,,,,,;;;;;;;::::ccccc
 .................................'',;;:cccccllllollllllllllccccclllc;',clc:;'.......................'''',:cccoOkc'''''''''''',,,,,,,,,,,;;;;;;:::::cc
 .................................'',,;::cccclllllccccccccccccccclll:,,;clcc:,,'.....................''.',::::ldl,''''''''''''''',,,,,,,,,,;;;;;::::::
 ..................................',,;;::cccclllccccccccccccllllllc:;,;;:::;,,''''..................''..,:;;;:c,''..''''''''''''''',,,,,,,,,,;;;;;:::
...................................'',,;::ccccllccccccccclllllllllllc:::;;;;;,,''....................,,..,;;,;;,''.....'.''''''''''''',,,,,,,,,;;;;;;;
....................................',,;:::cclllc:cc:::;::::::::::::;;;;,''..........................',..,;,',,'.............'''''''''''',,,,,,,,,;;;;
.....................................',,;::cclllc:::::;::::::;;;;;;;,,,''.......................''...',..',',,..................'''''''''''',,,,,,,,,;
......................................',;;:::clllc::cccccccllcccccccc:::;;,,,,''...............''....''..',,,'..'...................''''''''',,,,,,,,,
  .....................................',;;;::cclc::cccccccccccc::::;;;;;,,,,''''........................';:;.........................'''''''''''',,,,
   ....................................'',;;;::::::cc::cccccccc::;;,,,,,,''',,''........................',;l;............................''''''''''',,
   .....................................',,;;;:::::cccccc::::::::;;,,,,,,,',,,'''......................',';o;..............................'''''''''''
  .......................................',,,;;:::cccccccc::c::::::;;;::;;;;;,,'''.....................,'';l:'..................................''''''
     .....................................',,;;::::cccccccccccccclllccccc::::;;,,''...................''..,oo''...................................''''
     ................................ ....'',;;;;;;::cccccllccccclllcccc::::;;,,,''.......................'dk;.,'.....................................
     ...............................  ....''',;;;;;;;::cccclllccclcllccc::::;;,,''........................'o0o..,,....................................
     ............................      ......',,;;;;;;;:::cccccccllcc:::;;;;;,,,''........................'l0O,..::'..................................
     ..   .....................        .....'''',,,,,,;;::::::::cc:::;,,,,,,,,,,''........................,lOO:..':c:,'...............................
     .          ........              ......'''''',,,,,,;;::::;;;;;;;,'''''''''''.........................,lkk;...,cl:;,,''...........................
               ...                    ...'''''',,,,,,,,,;;;;;;;;,,,,,'''''................................,cxd,....;cc:,..''''''......................
                                      ...''''''',,,,,,;,,,,,,,,''''''''...................................':l:.....,:c:;'.........',,,,'..............
                                      ...''',,,,',,,,,;;;;,,,,,,,,,''''''..................................,;'......;cc:,'...........',;;;;;,'........
                                       ..''',,,;,,,,;;;;;;;,,,,,,,,''''''...................................... .....,::,'................';:c::;,....
                                       ..''',,;;;;;;;;;;;;;;;;;,,,,'''''''....................................  ......,;;'...................',;clll:;
									   
______________________________________________________________________________________________________________________________________________________
									   ${NC}"


send_command() {
    echo "$1" > "$FIFO_PATH"
    sleep 0.1
}



send_command ""

while IFS= read -r cmd
do
    if [[ -z "$cmd" || "$cmd" == \#* || "$cmd" == "remove" ]]; then
        continue
    fi
   echo -e "${YELLOW}Testing command: $cmd${NC}"

    bash -c "$cmd" > "$TEMP_DIR/bash_output" 2> "$TEMP_DIR/bash_error"

    truncate -s 0 "$TEMP_DIR/minishell_output"

    send_command "$cmd"

    sleep 0.1

    sed '1d;/minishell>/d' "$TEMP_DIR/minishell_output" > "$TEMP_DIR/minishell_processed"

    if ! diff -q "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed" >/dev/null
    then 
        echo -e "${RED}Diff KO :(${NC}"
        echo "Diff:"
        diff --color=always "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed"
        echo 
	else
		echo -e "${GREEN}Diff ok! :)${NC}"
    fi  

done < "$TEST_COMMANDS"

last_line=$(tail -n 1 "$TEST_COMMANDS")
if [[ "$last_line" == "remove" ]]; then
    echo -e "${RED}$TEST_COMMANDS removed${NC}"
    rm "$TEST_COMMANDS"
fi

cleanup