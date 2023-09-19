//LIBRARIES (10000 GB of ram required to run)
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <cstdlib>


//GLOBALLY DEFINED VARIABLES, REFERENCES, AND POINTERS (Segmentation Fault: Core Dumped)
int composer_number = 1;
int& rcomposer_number = composer_number;
int difficulty_level = 1;
int& rdifficulty_level = difficulty_level;
bool wanna_play = false;
bool& rwanna_play = wanna_play;
bool starting_anew = true;
bool rstarting_anew = starting_anew;
bool mixed_mode = false;
bool& rmixed_mode = mixed_mode;
double highest_score = 0;
double& rhighest_score = highest_score;
std::vector<bool> chosen_ones = { 1, 1, 1, 1, 1 };
std::vector<bool>& rchosen_ones = chosen_ones;


//CLASSES AND STRUCTURES (boiler plate city)
struct musicstructuring
{
    int FINAL_SYMPHONY;
    std::vector<int> SYMPHONY_SIZES;
    std::string NAME;

    //Constructor
    musicstructuring() : FINAL_SYMPHONY(0), SYMPHONY_SIZES(), NAME("") {}
    musicstructuring(int FINAL_SYMPHONY, std::vector<int> SYMPHONY_SIZES, std::string NAME) : FINAL_SYMPHONY(FINAL_SYMPHONY), SYMPHONY_SIZES(SYMPHONY_SIZES), NAME(NAME) {}
    //Copy Constructor (not needed but if i can figure out how to make these members const without everything breaking will be useful prolly maybe)
    musicstructuring(const musicstructuring& composer) : FINAL_SYMPHONY(composer.FINAL_SYMPHONY), SYMPHONY_SIZES(composer.SYMPHONY_SIZES), NAME(composer.NAME) {}
};
class MusicClip
{
private:
    std::string composer;
    int symphony_no;
    int movement_no;
public:
    //Constructor
    MusicClip(std::string composer, int symphony_no, int movement_no): composer(composer), symphony_no(symphony_no), movement_no(movement_no) {}
    //Encapsulators
    void setComposer(std::string composer) { this->composer = composer; }
    void setSymphonyNo(int symphony_no) { this->symphony_no = symphony_no; }
    void setMovementNo(int movement_no) { this->movement_no = movement_no; }
    std::string getComposer() { return composer; }
    int getSymphonyNo() { return symphony_no; }
    int getMovementNo() { return movement_no; }
    //Methods
    int guessComposer(int& hint_counter)
    {
        system("cls");
        std::string sing_plur_hint = hint_counter == 1 ? "hint" : "hints";
        std::string composer_guess;
        std::string hint_msg = hint_counter != 0 ? "Type 747 to hear another clip!\n" : "You can no longer get a hint!\n";
        std::cout << "Who was the composer?\nYou have " << hint_counter << " " << sing_plur_hint << " remaining. " << hint_msg << std::endl;
        std::cin >> composer_guess;

        if (composer_guess == getComposer()) //correct
        {
            system("COLOR 20");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Correct, that was made by " << getComposer() << ".\n";
            system("PAUSE");
            system("COLOR 07");
            return 2;
        }
        else if (composer_guess == "747")
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
    }
    int guessSymphonyNumber(int& hint_counter)
    {
        system("cls");
        std::string sing_plur_hint = hint_counter == 1 ? "hint" : "hints";
        int symph_no_guess;
        std::string hint_msg = hint_counter != 0 ? "Type 747 to hear another clip!\n" : "You can no longer get a hint!\n";
        std::cout << "What was the symphony number?\nYou have " << hint_counter << " " << sing_plur_hint << " remaining. " << hint_msg << std::endl;
        std::cin >> symph_no_guess;

        if (symph_no_guess == getSymphonyNo()) //correct
        {
            system("COLOR 20");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Correct, that was " << getComposer() << "'s Symphony No. " << getSymphonyNo() << ".\n";
            system("PAUSE");
            system("COLOR 07");
            return 2;
        }
        else if (symph_no_guess == 747)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
    }
    int guessMovementNumber(int& hint_counter)
    {
        system("cls");
        int move_no_guess;
        std::string sing_plur_hint = hint_counter == 1 ? "hint" : "hints";
        std::string hint_msg = hint_counter != 0 ? "Type 747 to hear another clip!\n" : "You can no longer get a hint!\n";
        std::cout << "What was the movement number?\nYou have " << hint_counter << " " << sing_plur_hint << " remaining. " << hint_msg << std::endl;
        std::cin >> move_no_guess;

        if (move_no_guess == getMovementNo()) //correct
        {
            system("COLOR 20");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Correct, that was " << getComposer() << "'s Symphony No. " << getSymphonyNo() << ", Movement "<< getMovementNo() << ".\n";
            system("PAUSE");
            system("COLOR 07");
            return 2;
        }
        else if (move_no_guess == 747)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
    }
};


//FUNCTIONS (spaghetti code)
int playAudioClip(std::string file_name, float play_duration) {
    // Load the audio file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(file_name)) {
        std::cerr << "Error loading audio file!" << std::endl;
        return -1;
    }

    // Create a sound instance and set the buffer
    sf::Sound sound;
    sound.setBuffer(buffer);

    // Get the audio duration
    float audio_duration = buffer.getDuration().asSeconds();

    if (play_duration > audio_duration) {
        std::cerr << "Play duration is longer than the audio duration." << std::endl;
        return -1;
    }

    // Generate a random starting point within the valid range
    float max_start_offset = audio_duration - play_duration;
    float random_start = static_cast<float>(std::rand()) / RAND_MAX * max_start_offset;

    // Set the starting point
    sound.setPlayingOffset(sf::seconds(random_start));

    // Play the audio for the specified duration
    sound.play();
    sf::sleep(sf::seconds(play_duration));

    return 0;
}
int getUserInput() 
{
    int userInput;
    while (true) {
        std::cout << "Enter a number: ";
        if (std::cin >> userInput) {
            // Input is a valid integer.
            // Clear any potential errors and discard extra input.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return userInput;
        }
        else {
            // Input is not a valid integer.
            std::cerr << "Invalid input. Please enter a valid number." << std::endl;
            // Clear the error state and discard extra input.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
double displayCurrentScore()
{
    std::ifstream read_current_score("current_score.txt");
    if (read_current_score.is_open())
    {
        double current_score;
        read_current_score >> current_score;
        read_current_score.close();
        return current_score;
    }
    else
    {
        read_current_score.close();
        std::ofstream write_current_score("current_score.txt");
        write_current_score << 0;
        return 0;
    }
}
double displayBestScore()
{
    std::ifstream read_best_score("best_score.txt");
    if (read_best_score.is_open())
    {
        double best_score;
        read_best_score >> best_score;
        read_best_score.close();
        return best_score;
    }
    else
    {
        read_best_score.close();
        std::ofstream write_best_score("best_score.txt");
        write_best_score << 0;
        return 0;
    }
}
void displayDifficulty()
{
    std::unordered_map<int, std::string> Composers;
    Composers[1] = "Mahler";
    Composers[2] = "Beethoven";
    Composers[3] = "Bruckner";
    Composers[4] = "Tchaikovsky";
    Composers[5] = "Schumann";
    std::unordered_map<int, std::string> Difficulties;
    Difficulties[1] = "Easy";
    Difficulties[2] = "Medium";
    Difficulties[3] = "Hard";
    Difficulties[4] = "Very Hard";
    std::vector<std::string> thebois = { Composers[1], Composers[2], Composers[3], Composers[4], Composers[5] };
    std::string mixed_msg = rmixed_mode == true ? "Mixed Mode On" : "Mixed Mode Off";
    std::vector<std::string> thefellas;
    std::string complist = "";
    for (int i = 0; i < thebois.size(); i++)
    {
        if (rchosen_ones[i] != 0)
        {
            thefellas.push_back(thebois[i]);
        }
    }
    for (int i = 0; i < thefellas.size(); i++)
    {
        complist += thefellas[i];
        complist += ", ";
    }
    if (rmixed_mode != true)
    {
        std::cout << mixed_msg << ".\nYou are on " << Composers[rcomposer_number] << " mode. You are on " << Difficulties[rdifficulty_level] << " difficulty.\n\n";
    }
    else
    {
        std::cout << mixed_msg << ".\nYour selected composers are " << complist << "and you are on " << Difficulties[rdifficulty_level] << " difficulty.\n\n";
    }
}
double loadHints()
{
    std::ifstream read_hints("hints.txt");
    if (read_hints.is_open())
    {
        int hints;
        read_hints >> hints;
        read_hints.close();
        return hints;
    }
    else
    {
        read_hints.close();
        std::ofstream write_hints("hints.txt");
        write_hints << 0;
        return 0;
    }
}
void resetCurrentScore()
{
    std::ifstream read_current_score("current_score.txt");
    std::ifstream read_best_score("best_score.txt");

    double current_score;
    double best_score;
    read_current_score >> current_score;
    read_best_score >> best_score;
    read_current_score.close();
    read_best_score.close();

    std::ofstream write_current_score("current_score.txt");
    std::ofstream write_best_score("best_score.txt");

    if (current_score > rhighest_score)
    {
        rhighest_score = current_score;
    }

    if (current_score > best_score)
    {
        write_current_score << 0;
        write_best_score << current_score;
    }
    else
    {
        write_current_score << 0;
        write_best_score << best_score;
    }
    write_current_score.close();
    write_best_score.close();
    return;
}
void addPoints(int amount, float multiplier)
{
    std::ifstream read_current_score("current_score.txt");
    double current_score;
    read_current_score >> current_score;
    read_current_score.close();

    double total = amount * multiplier;
    current_score += total;
    std::ofstream write_current_score("current_score.txt");
    write_current_score << current_score;
    write_current_score.close();
    
    std::ifstream read_best_score("best_score.txt");
    double best_score;
    read_best_score >> best_score;
    read_best_score.close();

    if (current_score > best_score)
    {
        std::ofstream write_best_score("best_score.txt");
        best_score = current_score;
        write_best_score << best_score;
        write_best_score.close();
    }
    if (current_score > rhighest_score)
    {
        rhighest_score = current_score;
    }
}
void selectComposer()
{
    system("cls");
    std::unordered_map<int, std::string> Composers;
    Composers[1] = "Mahler";
    Composers[2] = "Beethoven";
    Composers[3] = "Bruckner";
    Composers[4] = "Tchaikovsky";
    Composers[5] = "Schumann";
    std::cout << "You are currently on " << Composers[composer_number] << " mode.\n";
    do
    {
        std::cout << "Please select which composer you would like to hear." <<
            "\n0. Configure Mixed Mode\n1. Mahler\n2. Beethoven\n3. Bruckner\n4. Tchaikovsky\n5. Schumann\n";
        int selection = getUserInput();
        switch (selection)
        {
        case 0:
            do
            {
                std::vector<std::string> Names = { "Mahler", "Beethoven", "Bruckner", "Tchaikovsky", "Schumann" };
                std::cout << "Please input 1 for the composers you want and 0 for the composers you do not want.\n";
                system("PAUSE");
                for (int i = 0; i < Names.size(); i++)
                {
                    system("cls");
                    std::cout << Names[i] << "?\n";
                    int selection = getUserInput();
                    rchosen_ones[i] = selection;
                }
                std::cout << "You will see ";
                std::unordered_map<int, std::string> T_or_F;
                T_or_F[1] = "On";
                T_or_F[0] = "Off";
                for (int i = 0; i < chosen_ones.size(); i++)
                {
                    std::cout << Names[i] << ": " << T_or_F[chosen_ones[i]] << std::endl;
                }
                system("PAUSE");
                return;
            } while (true);
            break;  
        case 1:
            rcomposer_number = 1;
            std::cout << "Selecting " << Composers[composer_number] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 2:
            rcomposer_number = 2;
            std::cout << "Selecting " << Composers[composer_number] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 3:
            rcomposer_number = 3;
            std::cout << "Selecting " << Composers[composer_number] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 4:
            rcomposer_number = 4;
            std::cout << "Selecting " << Composers[composer_number] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 5:
            rcomposer_number = 5;
            std::cout << "Selecting " << Composers[composer_number] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        default:
            std::cout << "Invalid input, try again.\n";
        }
    } while (true);
    
}
int incorrectAnswer(MusicClip& clip)
{
    system("COLOR 47");
    std::cout << "Sorry, that's incorrect. The correct answer was " << clip.getComposer() << "'s Symphony No. " << clip.getSymphonyNo() << ", Movement " << clip.getMovementNo() << ".\n";
    system("PAUSE");
    system("COLOR 07");
    std::cout << "Your current score is " << displayCurrentScore() << ".\nYour highest session score is " << rhighest_score << "\nYour best score is " << displayBestScore() << ".\n";
    do
    {
        std::cout << "Would you like to hear another clip or return to main menu?\n" <<
            "0. Menu\n1. Another Clip\n";
        int selection;
        selection = getUserInput();

        switch (selection)
        {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            std::cerr << "Invalid input, try again.\n";
            break;
        }
    } while (true);
}
void useHint(std::string& file_name, float& play_duration, int& hint_counter)
{
    system("COLOR 90");
    if (hint_counter != 0)
    {
        hint_counter -= 1;
        std::cout << "Playing additional clip...";
        playAudioClip(file_name, play_duration);
        system("COLOR 07");
        return;
    }
    else
    {
        system("COLOR 07");
        std::cout << "Sorry, you have no more hints available!\n";
        system("PAUSE");
        return;
    }
}
void beginGuesses(std::string& file_name, float& play_duration, MusicClip& clip, musicstructuring& structuring, int& hint_counter, float& point_multiplier)
{
    bool mixed_mode_ip = true;
    int incorrect_selection;
    do
    {
        system("COLOR 07");
        if (rmixed_mode && mixed_mode_ip)
        {
            label:
                int guess;
                guess = clip.guessComposer(hint_counter);

                switch (guess)
                {
                case 0:
                    resetCurrentScore();
                    mixed_mode_ip = false;
                    incorrect_selection = incorrectAnswer(clip);
                
                    switch (incorrect_selection)
                    {
                    case 0:
                        rwanna_play = false;
                        rstarting_anew = true;
                        return;
                        break;
                    case 1:
                        rstarting_anew = true;
                        return;
                    }
                    break;
                case 1:
                    mixed_mode_ip = true;
                    useHint(file_name, play_duration, hint_counter);
                    goto label;
                    break;
                case 2:
                    addPoints(3, point_multiplier);
                    std::cout << "Your current score is " << displayCurrentScore() << ".\n";
                    mixed_mode_ip = false;
                    break;
            }
        }

        //symphony guessing
        label2:
            int symph_guess;
            symph_guess = clip.guessSymphonyNumber(hint_counter);
            switch (symph_guess)
            {
            case 0:
                resetCurrentScore();
                incorrect_selection = incorrectAnswer(clip);

                switch (incorrect_selection)
                {
                case 0:
                    rwanna_play = false;
                    rstarting_anew = true;
                    return;
                    break;
                case 1:
                    rstarting_anew = true;
                    return;
                }
                break;
            case 1:
                useHint(file_name, play_duration, hint_counter);
                goto label2;
                break;
            case 2:
                addPoints(5, point_multiplier);
                std::cout << "Your current score is " << displayCurrentScore() << ".\n";
                break;
            }

        //movement guessing
        label3:
            int move_guess;
            move_guess = clip.guessMovementNumber(hint_counter);
            switch (move_guess)
            {
            case 0:
                if (difficulty_level == 4)
                {
                    resetCurrentScore();
                }
                incorrect_selection = incorrectAnswer(clip);

                switch (incorrect_selection)
                {
                case 0:
                    rwanna_play = false;
                    rstarting_anew = true;
                    return;
                    break;
                case 1:
                    rstarting_anew = true;
                    return;
                    break;
                }
                break;
            case 1:
                useHint(file_name, play_duration, hint_counter);
                goto label3;
                break;
            case 2:
                system("cls");
                addPoints(10, point_multiplier);
                std::cout << "Your current score is " << displayCurrentScore() << ".\nYour highest session score is " << rhighest_score << "\nYour best score is " << displayBestScore() << ".\n";
                std::cout << "Would you like to hear another or return to the main menu?\n0. Menu\n1. Another Clip\n";
                int selection;
                selection = getUserInput();
                switch (selection)
                {
                case 0:
                    resetCurrentScore();
                    rwanna_play = false;
                    rstarting_anew = true;
                    return;
                    break;
                case 1:
                    rwanna_play = true;
                    rstarting_anew = false;
                    return;
                    break;
                default:
                    std::cerr << "Invalid input, try again.\n";
                    break;
                }
            }
    } while (true);
}
void playMahlerGame()
{
    rwanna_play = true;
    do
    {
        system("cls");
        musicstructuring MAHLER(10, { 5,5,6,4,5,4,5,2,4,5 }, "Mahler");
        musicstructuring BEETHOVEN(9, { 4,4,4,4,4,5,4,4,4 }, "Beethoven");
        musicstructuring BRUCKNER(9, { 4,4,4,4,4,4,4,4,3 }, "Bruckner");
        musicstructuring TCHAIK(6, { 4,4,5,4,4,4 }, "Tchaikovsky");
        musicstructuring SCHUMANN(4, { 4,4,5,4 }, "Schumann");
        std::unordered_map<int, musicstructuring> Number_To_Composer;
        Number_To_Composer[1] = MAHLER;
        Number_To_Composer[2] = BEETHOVEN;
        Number_To_Composer[3] = BRUCKNER;
        Number_To_Composer[4] = TCHAIK;
        Number_To_Composer[5] = SCHUMANN;
        std::vector<int> name_numbers = { 1, 2, 3, 4, 5 };
        std::vector<int> new_numbers;

        //generate random seed
        std::random_device rd;
        std::mt19937 mt(rd());

        if (rmixed_mode)
        {
            for (int i = 0; i < name_numbers.size(); i++)
            {
                int appendthis = name_numbers[i] * rchosen_ones[i];
                if (appendthis != 0)
                {
                    new_numbers.push_back(appendthis);
                }
            }
            std::uniform_int_distribution<int> random_index_seed(0, new_numbers.size() - 1);
            int random_index = random_index_seed(mt);
            composer_number = new_numbers[random_index];
        }
        //Generate random symphony by composer
        std::uniform_int_distribution<int> symphony_choices(1, Number_To_Composer[composer_number].FINAL_SYMPHONY);
        int random_symphony = symphony_choices(mt);

        //Generate random movement based on chosen symphony by composer
        int ran_symph_size = Number_To_Composer[composer_number].SYMPHONY_SIZES[random_symphony - 1];
        std::uniform_int_distribution<int> movement_choices(1, ran_symph_size);
        int random_movement = movement_choices(mt);


        //Create file name
        std::string symphony_string = std::to_string(random_symphony);
        std::string movement_string = std::to_string(random_movement);
        std::string file_name = Number_To_Composer[composer_number].NAME + "\\" + Number_To_Composer[composer_number].NAME + "." + symphony_string + "." + movement_string + ".wav";
        MusicClip clip(Number_To_Composer[composer_number].NAME, random_symphony, random_movement); //instantiates clip object based on randomized events above

        std::unordered_map<int, float> Difficulty_To_Time;
        Difficulty_To_Time[1] = 7.0;
        Difficulty_To_Time[2] = 5.0;
        Difficulty_To_Time[3] = 3.0;
        Difficulty_To_Time[4] = 1.5;

        float play_duration = Difficulty_To_Time[difficulty_level];
        int hint_counter;
        float point_multiplier;
        switch (difficulty_level) //gives # of hints based on difficulty, this was a dumb way to do it lmao but i dont feel like changing it rn
        {
        case 1:
            point_multiplier = .5;
            break;
        case 2:
            point_multiplier = 1;
            break;
        case 3:
            point_multiplier = 2;
            break;
        case 4:
            point_multiplier = 4;
            break;
        default:
            point_multiplier = .5;
            break;
        }
        if (rmixed_mode)
        {
            point_multiplier += 2;
        }
        if (rstarting_anew)
        {
            switch (difficulty_level)
            {
            case 1:
                hint_counter = 5;
                break;
            case 2:
                hint_counter = 3;
                break;
            case 3:
                hint_counter = 1;
                break;
            case 4:
                hint_counter = 0;
                break;
            default:
                hint_counter = 5;
            }
        }

        system("COLOR 17");
        std::cout << "Playing clip...";
        playAudioClip(file_name, play_duration);

        bool rwanna_play = true;
        beginGuesses(file_name, play_duration, clip, Number_To_Composer[composer_number], hint_counter, point_multiplier);
    } while (wanna_play);
}
void viewRules()
{
    do
    {
        system("cls");
        std::cout << "Please select what you would like to do.\n0. Menu\n1. View General Rules\n2. View Difficulty Rules\n3. View Special Input Rules\n";
        int selection;
        selection = getUserInput();
        switch (selection)
        {
        case 0:
            return;
            break;
        case 1:
            system("cls");
            std::cout << "You will hear a random section of a random symphony and movement.\n" <<
                "Depending on the difficulty, you will have to guess the composer, symphony number, and movement number.\n" <<
                "(you only have to guess the composer on mixed difficulty)\n" <<
                "Here are the points per type of question:\n\n" <<
                "|\t\tCOMPOSER GUESS: 3 POINTS\t\t|\n" <<
                "|\t\tSYMPHONY GUESS: 5 POINTS\t\t|\n" <<
                "|\t\tMOVEMENT GUESS: 10 POINTS\t\t|\n" <<
                "\nNote that leaving the game, changing the difficulty, or making errors will reset your current score.\n";
            system("PAUSE");
            break;
        case 2:
            system("cls");
            std::cout << "There are five difficulties: easy, medium, hard, very hard, and mixed.\n\n" <<
                "|\t\tEASY \t 7 SECOND CLIP \t POINT MULT = .5 \t MUST GUESS SYMPHONY, MOVEMENT OPTIONAL \t 5 HINTS\t\t|\n" <<
                "|\t\tMEDIUM \t 5 SECOND CLIP \t POINT MULT = 1 \t MUST GUESS SYMPHONY, MOVEMENT OPTIONAL \t 3 HINTS\t\t|\n" <<
                "|\t\tHARD \t 3 SECOND CLIP \t POINT MULT = 2 \t MUST GUESS SYMPHONY, MOVEMENT OPTIONAL \t 1 HINT\t\t\t|\n" <<
                "|\t\tV HARD \t 1.5 SEC CLIP \t POINT MULT = 4 \t MUST GUESS SYMPHONY AND MOVEMENT \t\t 0 HINTS\t\t|\n" <<
                "|\t\tMIXED \t NO EFFECT \t POINT MULT += 2 \t ALWAYS HAVE TO GUESS COMPOSER \t\t      NO EFFECT\t\t|\n";
            system("PAUSE");
            break;
        case 3:
            system("cls");
            std::cout << "There are some special inputs for specific composers:\n" <<
                "Mahler: Blumine is included as Symphony No. 1 Movement 5; Symphony 6 Mo 2 is the scherzo, Mo 3 is the andante.\n\n" <<
                "Bruckner: The study symphony is No. 10 and the 0th Symphony is No. 11. (not added yet cant find a good recording ;-;)\n";
            system("PAUSE");
            break;
        default:
            std::cerr << "Invalid input, try again.\n";
            break;
        }

    } while (true);
}
void setDifficulty()
{
    system("cls");
    std::unordered_map<int, std::string> Difficulty_Names;
    Difficulty_Names[1] = "Easy";
    Difficulty_Names[2] = "Medium";
    Difficulty_Names[3] = "Hard";
    Difficulty_Names[4] = "Very Hard";
    std::string mixed_msg = rmixed_mode == true ? "Turning off mixed mode, " : "Turning on mixed mode, ";
    std::cout << "You are currently on " << Difficulty_Names[difficulty_level] << " mode.\n";
    do
    {
        std::cout << "Please select which difficulty you would like to play on." <<
            "\n1. Easy\n2. Medium\n3. Hard\n4. Very Hard\n5. Mixed Composers\n";
        int selection = getUserInput();
        switch (selection)
        {
        case 1:
            rdifficulty_level = 1;
            std::cout << "Selecting " << Difficulty_Names[difficulty_level] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 2:
            rdifficulty_level = 2;
            std::cout << "Selecting " << Difficulty_Names[difficulty_level] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 3:
            rdifficulty_level = 3;
            std::cout << "Selecting " << Difficulty_Names[difficulty_level] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 4:
            rdifficulty_level = 4;
            std::cout << "Selecting " << Difficulty_Names[difficulty_level] << " mode, returning to main menu...\n";
            system("PAUSE");
            return;
        case 5:
            if (rmixed_mode == true)
            {
                rmixed_mode = false;
            }
            else
            {
                rmixed_mode = true;
            }
            std::cout << mixed_msg << "returning to main menu...\n";
            system("PAUSE");
            return;
        default:
            std::cout << "Invalid input, try again.\n";
            break;
        }
    } while (true);
}
void startGame()
{
    std::cout << "The Composer Game Version 2.0 by Alex Huff\nInitializing...Please press enter to continue\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    {
        system("cls");
        displayCurrentScore();
        displayBestScore();
        std::cout << "Your highest session score is " << rhighest_score << ". Your best score is " << displayBestScore() << ".\n\n";
        displayDifficulty();
        std::cout << "Welcome to the Composer Game Menu. Please choose an option:"
            << "\n0. Exit\n1. Play Game\n2. View Rules\n3. Select Composer\n4. Set Difficulty\n";
        int selection = getUserInput();
        switch (selection)
        {
        case 0:
            return;
        case 1:
            playMahlerGame();
            break;
        case 2:
            viewRules();
            break;
        case 4:
            setDifficulty();
            break;
        case 3:
            selectComposer();
        default:
            std::cout << "Invalid input, try again.\n";
            break;
        }
    } while (true);
}



//MAIN :)
int main()
{
    startGame();
}