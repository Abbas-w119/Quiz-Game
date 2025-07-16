#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    int correctAnswerIndex;
};

void displayQuestion(const Question& question, int questionNumber) {
    cout << "\nQuestion " << questionNumber << ": " << question.questionText << endl;
    for (size_t i = 0; i < question.options.size(); i++) {
        cout << i + 1 << ". " << question.options[i] << endl;
    }
    cout << "Your answer (1-4 or 0 to quit): ";
}

bool askQuestions(const vector<Question>& questions, int& score) {
    for (size_t i = 0; i < questions.size(); i++) {
        displayQuestion(questions[i], i + 1);
        int answer;
        cin >> answer;

        if (answer == 0) {
            cout << "\nYou chose to quit the quiz." << endl;
            return false;
        }

        while (answer < 0 || answer > 4) {
            cout << "Invalid input. Please choose an option between 1 and 4, or 0 to quit: ";
            cin >> answer;

            if (answer == 0) {
                cout << "\nYou chose to quit the quiz." << endl;
                return false;
            }
        }

        if (answer - 1 == questions[i].correctAnswerIndex) {
            cout << "Correct!" << endl;
            score++;
        } else {
            cout << "Wrong! The correct answer was: "
                 << questions[i].options[questions[i].correctAnswerIndex] << endl;
        }
    }
    return true;
}

void saveUserRecord(const string& userName, int score) {
    ofstream outFile("user_records.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "User: " << userName << ", Score: " << score << endl;
        outFile.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

void searchUserRecord(const string& searchName) {
    ifstream inFile("user_records.txt");
    string line;
    bool found = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find("User: " + searchName) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            cout << "No records found for user: " << searchName << endl;
        }
    } else {
        cout << "Error opening file for reading." << endl;
    }
}

void quizMenu() {
    vector<Question> easyCapitalsQuestions;
    vector<Question> easyGeneralKnowledgeQuestions;
    vector<Question> easyMathsQuestions;
    vector<Question> hardProgrammingQuestions;
    vector<Question> hardScienceQuestions;
    vector<Question> hardHistoryQuestions;
    int score = 0;
    string userName;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, userName);

    easyCapitalsQuestions = {
        {"What is the capital of France?", {"Berlin", "Madrid", "Paris", "Rome"}, 2},
        {"What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Bangkok"}, 2},
        {"What is the capital of Canada?", {"Toronto", "Ottawa", "Vancouver", "Montreal"}, 1},
        {"What is the capital of Australia?", {"Sydney", "Melbourne", "Canberra", "Brisbane"}, 2},
        {"What is the capital of South Africa?", {"Cape Town", "Pretoria", "Johannesburg", "Durban"}, 1},
        {"What is the capital of Germany?", {"Berlin", "Vienna", "Zurich", "Hamburg"}, 0},
        {"What is the capital of Italy?", {"Rome", "Milan", "Naples", "Florence"}, 0},
        {"What is the capital of the United Kingdom?", {"Edinburgh", "Cardiff", "London", "Belfast"}, 2},
        {"What is the capital of the United States?", {"New York", "Washington D.C.", "Los Angeles", "Chicago"}, 1},
        {"What is the capital of India?", {"Mumbai", "New Delhi", "Kolkata", "Chennai"}, 1},
        {"What is the capital of China?", {"Shanghai", "Beijing", "Shenzhen", "Chengdu"}, 1},
        {"What is the capital of Brazil?", {"Rio de Janeiro", "Brasilia", "Sao Paulo", "Salvador"}, 1},
        {"What is the capital of Russia?", {"Moscow", "Saint Petersburg", "Kazan", "Sochi"}, 0},
        {"What is the capital of Egypt?", {"Cairo", "Alexandria", "Giza", "Luxor"}, 0},
        {"What is the capital of Mexico?", {"Guadalajara", "Cancun", "Mexico City", "Monterrey"}, 2}
    };

    easyGeneralKnowledgeQuestions = {
        {"Which planet is known as the Red Planet?", {"Earth", "Venus", "Mars", "Jupiter"}, 2},
        {"Who wrote 'Hamlet'?", {"Charles Dickens", "William Shakespeare", "Mark Twain", "Jane Austen"}, 1},
        {"Which year did World War II end?", {"1943", "1944", "1945", "1946"}, 2},
        {"Who painted the Mona Lisa?", {"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Claude Monet"}, 2},
        {"What is the largest ocean on Earth?", {"Atlantic", "Indian", "Pacific", "Arctic"}, 2},
        {"What is the smallest country in the world?", {"Monaco", "San Marino", "Vatican City", "Liechtenstein"}, 2},
        {"Which element has the highest melting point?", {"Tungsten", "Carbon", "Osmium", "Iron"}, 0},
        {"Who developed the theory of relativity?", {"Isaac Newton", "Albert Einstein", "Galileo Galilei", "Nikola Tesla"}, 1},
        {"What is the longest river in the world?", {"Nile", "Amazon", "Yangtze", "Mississippi"}, 1},
        {"What is the hardest natural substance on Earth?", {"Gold", "Iron", "Diamond", "Platinum"}, 2},
        {"Which ancient wonder was located in Babylon?", {"Great Pyramid", "Hanging Gardens", "Statue of Zeus", "Colossus of Rhodes"}, 1},
        {"Who is known as the 'Father of Computers'?", {"Charles Babbage", "Alan Turing", "John von Neumann", "Konrad Zuse"}, 0},
        {"Which gas makes up the majority of Earth's atmosphere?", {"Oxygen", "Nitrogen", "Carbon Dioxide", "Helium"}, 1},
        {"What is the SI unit of electric current?", {"Volt", "Ampere", "Ohm", "Watt"}, 1},
        {"Which metal is liquid at room temperature?", {"Mercury", "Gallium", "Bromine", "Sodium"}, 0}
    };

    easyMathsQuestions = {
        {"What is 5 + 3?", {"5", "8", "10", "12"}, 1},
        {"What is 12 * 12?", {"124", "144", "164", "184"}, 1},
        {"What is 15 % 4?", {"2", "3", "4", "5"}, 1},
        {"What is 2^10?", {"1024", "2048", "512", "256"}, 0},
        {"What is 25 * 25?", {"525", "625", "725", "825"}, 1},
        {"What is the square root of 256?", {"12", "14", "16", "18"}, 2},
        {"Solve: (15 + 25) * 2", {"60", "70", "80", "90"}, 2},
        {"What is the value of pi to 3 decimal places?", {"3.141", "3.142", "3.143", "3.144"}, 0},
        {"What is the derivative of x^2?", {"2x", "x^2", "x", "2"}, 0},
        {"What is 1001 divided by 7?", {"143", "142", "144", "145"}, 0},
        {"What is the factorial of 5?", {"120", "100", "60", "20"}, 0},
        {"What is the sum of the first 10 natural numbers?", {"50", "55", "60", "65"}, 1},
        {"If a triangle has sides 3, 4, and 5, what type of triangle is it?", {"Equilateral", "Isosceles", "Scalene", "Right-angled"}, 3},
        {"What is the integral of 1/x dx?", {"log(x)", "1/x", "x", "x^2"}, 0},
        {"What is the value of 7! (7 factorial)?", {"5040", "4030", "5030", "6040"}, 0}
    };

    hardProgrammingQuestions = {
        {"Which language is used for web apps?", {"C++", "Python", "JavaScript", "Java"}, 2},
        {"Which symbol is used for comments in C++?", {"//", "/* */", "Both", "None"}, 2},
        {"Which header file is needed for input/output in C++?", {"iostream", "stdio.h", "string", "math.h"}, 0},
        {"What is a loop that never ends called?", {"While loop", "Infinite loop", "For loop", "Do-while loop"}, 1},
        {"Which of these is not a programming language?", {"HTML", "Python", "C++", "Java"}, 0},
        {"What is the output of 5 + 2 * 3 in C++?", {"21", "11", "17", "None"}, 1},
        {"Which data type is used to create a variable that should store text?", {"int", "string", "char", "float"}, 1},
        {"What is the size of an int in C++ on most modern systems?", {"2 bytes", "4 bytes", "8 bytes", "Depends on the system"}, 1},
        {"What does OOP stand for?", {"Object-Oriented Programming", "Object-Operation Processing", "Order of Processing", "None of these"}, 0},
        {"Which keyword is used to define a constant in C++?", {"constant", "const", "final", "static"}, 1},
        {"Which operator is used to access a member of a structure?", {"->", ".", "::", "*"}, 1},
        {"Which function is used to read a single character in C++?", {"getchar()", "cin.get()", "getch()", "getc()"}, 1},
        {"What is the result of the expression true && false in C++?", {"true", "false", "1", "0"}, 1},
        {"Which feature in C++ allows multiple functions to have the same name?", {"Inheritance", "Polymorphism", "Function Overloading", "Encapsulation"}, 2},
        {"Which of the following is not a valid variable name in C++?", {"myVariable", "2ndVar", "_temp", "variable_1"}, 1}
    };

    hardScienceQuestions = {
        {"What is the chemical symbol for Potassium?", {"P", "K", "Pt", "Po"}, 1},
        {"Which planet is closest to the Sun?", {"Venus", "Mars", "Mercury", "Earth"}, 2},
        {"Who is known as the father of quantum mechanics?", {"Albert Einstein", "Niels Bohr", "Max Planck", "Erwin Schrodinger"}, 2},
        {"What is the speed of light in a vacuum?", {"300,000 km/s", "150,000 km/s", "400,000 km/s", "200,000 km/s"}, 0},
        {"What is the most abundant gas in Earth's atmosphere?", {"Oxygen", "Hydrogen", "Nitrogen", "Carbon Dioxide"}, 2},
        {"What is the powerhouse of the cell?", {"Nucleus", "Mitochondria", "Ribosome", "Golgi Apparatus"}, 1},
        {"What is the chemical formula for table salt?", {"NaCl", "KCl", "CaCl2", "MgCl2"}, 0},
        {"Who proposed the theory of evolution by natural selection?", {"Isaac Newton", "Charles Darwin", "Gregor Mendel", "Albert Einstein"}, 1},
        {"What is the main gas found in the air we breathe?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Hydrogen"}, 2},
        {"What planet is known as the Earth's twin?", {"Mars", "Venus", "Jupiter", "Saturn"}, 1},
        {"What is the largest organ in the human body?", {"Heart", "Liver", "Skin", "Lungs"}, 2},
        {"What is the unit of electrical resistance?", {"Volt", "Ohm", "Watt", "Ampere"}, 1},
        {"What is the pH of pure water?", {"5", "6", "7", "8"}, 2},
        {"Who discovered penicillin?", {"Marie Curie", "Alexander Fleming", "Louis Pasteur", "Isaac Newton"}, 1},
        {"What force keeps us on the ground?", {"Magnetism", "Gravity", "Electricity", "Friction"}, 1}
    };

    hardHistoryQuestions = {
        {"Who was the first president of the United States?", {"George Washington", "Thomas Jefferson", "John Adams", "Benjamin Franklin"}, 0},
        {"What year did the Titanic sink?", {"1910", "1911", "1912", "1913"}, 2},
        {"Who was known as the Iron Lady?", {"Margaret Thatcher", "Queen Victoria", "Marie Curie", "Florence Nightingale"}, 0},
        {"Which war was fought between the North and South regions in the United States?", {"World War I", "World War II", "Civil War", "Vietnam War"}, 2},
        {"In which year did the Berlin Wall fall?", {"1987", "1988", "1989", "1990"}, 2},
        {"Who was the first man to step on the moon?", {"Neil Armstrong", "Buzz Aldrin", "Yuri Gagarin", "Michael Collins"}, 0},
        {"Which ancient civilization built the pyramids?", {"Romans", "Greeks", "Egyptians", "Mayans"}, 2},
        {"Who was the leader of the Soviet Union during World War II?", {"Joseph Stalin", "Vladimir Lenin", "Leon Trotsky", "Nikita Khrushchev"}, 0},
        {"What was the name of the ship that brought the Pilgrims to America in 1620?", {"Mayflower", "Santa Maria", "Pinta", "Nina"}, 0},
        {"Who was the main author of the Declaration of Independence?", {"Thomas Jefferson", "John Adams", "Benjamin Franklin", "James Madison"}, 0},
        {"Who was the British monarch during World War I?", {"Queen Victoria", "King George V", "King Edward VII", "Queen Elizabeth II"}, 1},
        {"Which empire was known as the 'Land of the Rising Sun'?", {"Chinese Empire", "Roman Empire", "Japanese Empire", "Mongol Empire"}, 2},
        {"What year did the American Civil War end?", {"1863", "1864", "1865", "1866"}, 2},
        {"Who discovered America in 1492?", {"Christopher Columbus", "Ferdinand Magellan", "Vasco da Gama", "John Cabot"}, 0},
        {"What was the name of the first successful English colony in America?", {"Plymouth", "Roanoke", "Jamestown", "Salem"}, 2},
    };

    int levelChoice, categoryChoice;

    cout << "\nChoose a level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Hard" << endl;
    cout << "Your choice: ";
    cin >> levelChoice;

    if (levelChoice == 1) {
        cout << "\nYou chose Easy level." << endl;
        cout << "Choose a category:" << endl;
        cout << "1. Capitals" << endl;
        cout << "2. General Knowledge" << endl;
        cout << "3. Maths" << endl;
        cout << "Your choice: ";
        cin >> categoryChoice;

                switch (categoryChoice) {
            case 1:
                cout << "\nYou chose Capitals." << endl;
                askQuestions(easyCapitalsQuestions, score);
                break;
            case 2:
                cout << "\nYou chose General Knowledge." << endl;
                askQuestions(easyGeneralKnowledgeQuestions, score);
                break;
            case 3:
                cout << "\nYou chose Maths." << endl;
                askQuestions(easyMathsQuestions, score);
                break;
            default:
                cout << "Invalid choice. Exiting the quiz." << endl;
                return;
        }

    } else if (levelChoice == 2) {
        cout << "\nYou chose Hard level." << endl;
        cout << "Choose a category:" << endl;
        cout << "1. Programming" << endl;
        cout << "2. Science" << endl;
        cout << "3. History" << endl;
        cout << "Your choice: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1:
                cout << "\nYou chose Programming." << endl;
                askQuestions(hardProgrammingQuestions, score);
                break;
            case 2:
                cout << "\nYou chose Science." << endl;
                askQuestions(hardScienceQuestions, score);
                break;
            case 3:
                cout << "\nYou chose History." << endl;
                askQuestions(hardHistoryQuestions, score);
                break;
            default:
                cout << "Invalid choice. Exiting the quiz." << endl;
                return;
        }
    } else {
        cout << "Invalid level choice. Exiting the quiz." << endl;
        return;
    }

    saveUserRecord(userName, score);
    cout << "\nQuiz Over, " << userName << "! Your final score is: " << score << "/15." << endl;
}

int main() {
    int mainChoice;

    while (true) {
        cout << "\nMain Menu:" << endl;
        cout << "1. Take the Quiz" << endl;
        cout << "2. Search for a User's Record" << endl;
        cout << "3. Exit" << endl;
        cout << "Your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                quizMenu();
                break;
            case 2: {
                string searchName;
                cout << "Enter the user's name to search: ";
                cin.ignore();
                getline(cin, searchName);
                searchUserRecord(searchName);
                break;
            }
            case 3:
                cout << "Exiting. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose again." << endl;
        }
    }

    return 0;
}

