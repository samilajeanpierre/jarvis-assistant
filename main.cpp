#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    string command;

    cout << "🤖  JARVIS Online. Type 'help' for a list of commands.\n\n";

    while (true) {
        cout << "You: ";
        getline(cin, command);

        // make command lowercase
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "exit") {
            cout << "JARVIS: Goodbye, my friend.\n";
            system("espeak 'Goodbye my friend'");
            break;
        } 
        else if (command == "help") {
            cout << "JARVIS: Available commands:\n";
            cout << "  hello     - greet JARVIS\n";
            cout << "  time      - show current system time\n";
            cout << "  pathfind  - run your pathfinder algorithm\n";
            cout << "  chat      - talk with GPT AI\n";
            cout << "  exit      - close JARVIS\n";
            system("espeak 'Here are my available commands: hello, time, pathfind, chat, and exit.'");
        } 
        else if (command == "hello") {
            cout << "JARVIS: Hello there! How can I assist you today?\n";
            system("espeak 'Hello there. How can I assist you today'");
        } 
        else if (command == "time") {
            cout << "JARVIS: The current system time is:\n";
            system("date");
        } 
        else if (command == "pathfind") {
            cout << "JARVIS: Launching pathfinder module...\n\n";
            system("~/cpp_projects/pathfinder/pathfinder");
        }
        else if (command == "chat") {
            cout << "JARVIS: Would you like me to use live news or just my knowledge? (type 'live' or 'normal')\nYou: ";
            string mode;
            getline(cin, mode);
            transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

            cout << "JARVIS: Ask me anything.\nYou: ";
            string userPrompt;
            getline(cin, userPrompt);

            string context = "";

            if (mode == "live") {
                cout << "JARVIS: Fetching recent web info...\n";
                system("curl -s 'https://newsapi.org/v2/top-headlines?country=us&apiKey=$NEWS_API_KEY' | jq -r '.articles[0:3] | map(.title + \" - \" + .description) | join(\". \")' > news.txt");
                context = "$(cat news.txt)";
            }

            string apiCall = "curl https://api.openai.com/v1/chat/completions "
                "-s -H \"Content-Type: application/json\" "
                "-H \"Authorization: Bearer $OPENAI_API_KEY\" "
                "-d '{\"model\": \"gpt-4o-mini\", "
                "\"messages\": [{\"role\": \"system\", \"content\": \"You are Jarvis, an AI assistant.\"}, "
                "{\"role\": \"user\", \"content\": \"" + context + " " + userPrompt + "\"}], "
                "\"max_tokens\": 200}' | jq -r '.choices[0].message.content' > response.txt";

            system(apiCall.c_str());
            cout << "JARVIS: ";
            system("cat response.txt");
            cout << endl;
            system("espeak -f response.txt");
        }
        else {
            cout << "JARVIS: Sorry, I don't recognize that command.\n";
            system("espeak 'Sorry, I do not recognize that command'");
        }

        cout << "\n";
    }

    return 0;
}
