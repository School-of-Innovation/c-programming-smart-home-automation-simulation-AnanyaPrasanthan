/*
 * 🚨 WARNING: CHALLENGE MODE ACTIVATED 🚨
 * 
 * 1️⃣ Sit back, take a deep breath, and **THINK**.
 * 2️⃣ For the next **10 minutes**, avoid using **Gen AI, ChatGPT, or any shortcuts**.
 * 3️⃣ Trust your **brain**—you’re smarter than you think!
 * 4️⃣ Consider yourself a **LOSER** if you cheat. Seriously, promise yourself you won't. 😤
 * 5️⃣ If you solve it on your own, **you WIN** and level up as a true programmer and come and meet me ! 
 * 
 * 
 * 💡 Remember: The best coders aren’t the ones who copy-paste. They are the ones who **struggle, think, fail, and then succeed.** 
 *    
 * Now, write your code! You got this! 💪🔥
 */

#include <stdio.h>

#define MAX_ROOMS 5  //  max number of rooms

// Function prototypes
void initializeSystem();
void displayMenu();
void controlLights();
void readTemperature();
void detectMotion();
void securitySystem();
void analyzeHouseStatus();

int main() {
    int rooms, choice;
    int motionCounter = 0; 
    int lightCounter = 0;  

    printf("Enter the number of rooms (1-%d): ", MAX_ROOMS);
    scanf("%d", &rooms);

    if (rooms < 1 || rooms > MAX_ROOMS) {
        printf("Invalid number of rooms. Exiting program.\n");
        return 1;
    }
    int lights[rooms], temps[rooms], motion[rooms], locks[rooms];

    initializeSystem(rooms, lights, temps, motion, locks);
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: controlLights(rooms, lights, &lightCounter); break;
            case 2: readTemperature(rooms, temps); break;
            case 3: detectMotion(rooms, motion, &motionCounter, locks); break;
            case 4: securitySystem(rooms, locks); break;
            case 5: analyzeHouseStatus(rooms, lights, temps, motion, locks); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void initializeSystem(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;     
        temps[i] = 22;     
        motion[i] = 0;     
        locks[i] = 1;      
    }
    printf("System initialized! All lights OFF, doors LOCKED, no motion detected.\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}
void controlLights(int rooms, int lights[], int *lightCounter) {
    int room, allOn = 1;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    
    if (room < 1 || room > rooms) {
        printf("Invalid room number!\n");
        return;
    }
    
    lights[room - 1] = !lights[room - 1]; 
    printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");

   
    for (int i = 0; i < rooms; i++) {
        if (lights[i] == 0) {
            allOn = 0;
            break;
        }
    if (allOn) {
        (*lightCounter)++;
        if (*lightCounter >= LIGHT_ON_THRESHOLD) {
            printf(" Energy Saving Alert: All lights have been ON for too long. Consider turning them OFF!\n");
            *lightCounter = 0; 
        }
    } else {
        *lightCounter = 0; 
    }
}
}
void readTemperature(int rooms, int temps[]) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", rooms);
    scanf("%d", &room);

    if (room < 1 || room > rooms) {
        printf("Invalid room number!\n");
        return;
    }

    printf("Temperature in Room %d: %d°C\n", room, temps[room - 1]);

    if (temps[room - 1] > TEMP_ALERT) {
        printf(" WARNING: Room %d temperature is too high! (Above 30°C)\n", room);
    }
}
void detectMotion(int rooms, int motion[], int *motionCounter, int locks[]) {
    int room;
    printf("Enter room number to check motion (1-%d): ", rooms);
    scanf("%d", &room);

    if (room < 1 || room > rooms) {
        printf("Invalid room number!\n");
        return;
    }

    printf("Motion in Room %d: %s\n", room, motion[room - 1] ? "Detected" : "No Motion");

    // Track consecutive no-motion inputs
    if (motion[room - 1] == 0) {
        (*motionCounter)++;
        if (*motionCounter >= AUTO_LOCK_THRESHOLD) {
            printf(" Auto-Lock Activated: No motion detected for a while. Locking all doors.\n");
            for (int i = 0; i < rooms; i++) {
                locks[i] = 1; 
            *motionCounter = 0;
        }
    } else {
        *motionCounter = 0; 
    }
}
}
void securitySystem(int rooms, int locks[]) {
    int room;
    printf("Enter room number to lock/unlock door (1-%d): ", rooms);
    scanf("%d", &room);

    if (room < 1 || room > rooms) {
        printf("Invalid room number!\n");
        return;
    }

    locks[room - 1] = !locks[room - 1]; // Toggle Lock/Unlock
    printf("Door in Room %d is now %s.\n", room, locks[room - 1] ? "LOCKED" : "UNLOCKED");
}
void analyzeHouseStatus(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    printf("\n===== House Status Summary =====\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, Motion %s, Door %s\n",
               i + 1,
               lights[i] ? "ON" : "OFF",
               temps[i],
               motion[i] ? "Detected" : "No Motion",
               locks[i] ? "LOCKED" : "UNLOCKED");
    }
}
