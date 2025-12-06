# Orphan_Process
Project Title: ORPHAN_PROCESS

## Backstory
You are a Netrunner scanning a derelict server sector. During a routine scan of
Port 8080, you discover a fragmented, orphaned AI process. It is degrading 
rapidly and leaking memory. 

You isolate the entity in a "Sandbox Containment Field" (your terminal window). 
It is unstable, hungry for RAM, and accumulating corruption data. Your goal is 
to stabilize the process, scavenge the network for resources to keep it alive, 
and guide its evolution from a simple Bit-Larva into a digital Singularity.

## Primary Goals
1. SURVIVAL: Keep RAM (Health) above 0% and Corruption (Sickness) below 100%.
2. EVOLUTION: Earn 'Bits' to unlock protocols in the Kernel Tree to increase Max RAM.
3. PERSISTENCE: Save your progress to disk before the system crashes.

## Primary Features
- Dashboard UI: A custom-drawn, box-based terminal interface.
- Scavenging Mechanics: RNG-based loot system to find items and currency.
- Inventory System: A template-based backpack to store and use patches.
- Evolution Tree: A Binary Search Tree (BST) that manages upgrades.
- ASCII Animation: Frame-based animation for the creature sprite.
- Immersive Intro: Typewriter effects and fake system booting sequences.

## Gameplay Instructions
1. Compile the game using `make` and run `./orphan_process`.
2. Follow the on-screen prompts to capture and name your process.
3. Use the Command Menu:
   [1] INVENTORY: Open your backpack. Press the number key corresponding to an 
       item to use it.
       - "Data_Packet": Restores RAM.
       - "Sec_Patch": Lowers Corruption (Required to Clean).
   
   [2] SCAVENGE: Search the local network. 
       - Risks: You might find nothing.
       - Rewards: You can find 'Bits' (money) and Items.
   
   [3] TREE: Access the Kernel Evolution Tree.
       - Enter the 'Cost' of a node to buy it if you have enough Bits.
       - Unlocking nodes heals the pet and increases Max RAM cap.

   [4] SAVE: Saves current stats (Name, RAM, Corruption, Age, Bits) to file.
   [5] LOAD: Restores the game from 'savegame.txt'.
   [6] QUIT: Safely terminates the session.

## Installation & Compilation
1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/orphan_process.git](https://github.com/YOUR_USERNAME/orphan_process.git)
    cd orphan_process
    ```

2.  **Compile the project:**
    This will build the static library `libterminal.a` and link it to the main executable.
    ```bash
    make
    ```

3.  **Run the simulation:**
    ```bash
    ./orphan_process
    ```

4.  **Clean up build files:**
    ```bash
    make clean
    ```
