# :pager: The Core War project

The project is the implementation of [Core War Game](https://en.wikipedia.org/wiki/Core_War).

There are **champs** (bots in abstract assembly language called Redcode), **compiler** (produces bytecode versions of champs) and **virtual machine** (executes provided bytecode).

Virtual machine has a pretty UI, which shows its 'memory dump' with bots code and carrets for each cycle (and some other shiny things).

![Corewar in action](/resources/corewar_in_action.gif)

## How to run on Ubuntu?

* install ncurses library: `sudo apt-get install libncurses-dev -y`
* run `git clone --recurse-submodules https://github.com/ollevche/corewar && cd corewar`
* compile asm and vm binaries: `make`
* compile bots: `./asm champs/helltrain.s champs/omegabot.s`
* run vm with UI enabled: `./corewar -v champs/helltrain.cor champs/omegabot.cor`
