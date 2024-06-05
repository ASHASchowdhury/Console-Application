#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Function to get user input
string getUserInput() {
    string input;
    cout << "> ";
    getline(cin, input);
    return input;
}

// Function to check if a string contains a certain substring
bool contains(string str, string substr) {
    return str.find(substr) != string::npos;
}

// Function to perform sentiment analysis (basic keyword matching)
string analyzeSentiment(string user_input) {
    // Keywords for positive, negative, and neutral sentiments
    vector<string> positive_keywords = {"happy", "joyful", "excited", "great", "awesome", "fantastic", "amazing", "delighted", "ecstatic", "thrilled", "cheerful"};
    vector<string> negative_keywords = {"sad", "unhappy", "disappointed", "angry", "upset", "depressed", "miserable", "frustrated", "annoyed", "angry", "stressed"};
    vector<string> neutral_keywords = {"okay", "fine", "alright", "neutral", "so-so", "indifferent", "calm", "composed", "unaffected", "moderate"};

    // Convert input to lowercase for case-insensitive matching
    transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

    // Check for positive sentiment
    for (const string& keyword : positive_keywords) {
        if (contains(user_input, keyword))
            return "positive";
    }

    // Check for negative sentiment
    for (const string& keyword : negative_keywords) {
        if (contains(user_input, keyword))
            return "negative";
    }

    // Default to neutral sentiment if neither positive nor negative keywords are found
    return "neutral";
}

// Function to generate bot response based on sentiment
string getBotResponse(string sentiment) {
    if (sentiment == "positive")
        return "I'm glad to hear that you're feeling positive!";
    else if (sentiment == "negative")
        return "I'm sorry to hear that you're feeling down. Is there anything I can do to help?";
    else
        return "It's good to check in with your emotions.";
}

// Function to generate bot response based on conversation topics
string getAdvancedBotResponse(string user_input, map<string, string>& learned_responses) {
    // Define conversation topics and corresponding responses
    map<string, string> topics = {
        {"hello", "Hello! How are you today?"},
        {"how are you", "I'm just a bot, but thank you for asking!"},
        {"weather", "I'm sorry, I'm not equipped to check the weather."},
        {"thanks", "You're welcome!"},
        {"bye", "Goodbye! Have a great day."},
        {"sing", "♪ La la la, I'm singing a happy tune! ♪"},
        {"joke", "Why don't scientists trust atoms? Because they make up everything!"},
        {"cheer up", "Think of three things you're grateful for, and smile!"},
        {"watch a funny video", "Check out some funny cat videos on YouTube!"},
        {"go for a walk", "Take a stroll outside and enjoy the fresh air."}
    };

    // Check for known conversation topics
    for (const auto& [topic, response] : topics) {
        if (contains(user_input, topic))
            return response;
    }

    // Check if the user input matches a learned response
    for (const auto& [expression, response] : learned_responses) {
        if (contains(user_input, expression))
            return response;
    }

    // Default response if no specific topic or learned expression is identified
    return "I'm sorry, I don't understand. Can you please rephrase?";
}

int main() {
    cout << "Hi Labib Boss, I'm your Jarvis.\n";
    cout << "Tell me how you feel. You can start chatting. Type 'exit' to end the conversation.\n\n";

    map<string, string> learned_responses; // Store learned expressions and responses

    // Main chat loop
    while (true) {
        string user_input = getUserInput();
        if (user_input == "exit") {
            cout << "Goodbye! Have a great day.\n";
            break;
        }
        string sentiment = analyzeSentiment(user_input);
        string bot_response;
        if (sentiment != "neutral") {
            bot_response = getBotResponse(sentiment);
        } else {
            bot_response = getAdvancedBotResponse(user_input, learned_responses);
            if (bot_response == "I'm sorry, I don't understand. Can you please rephrase?") {
                cout << "Jarvis: " << bot_response << endl;
                cout << "You: ";
                string correct_response = getUserInput();
                learned_responses[user_input] = correct_response;
                cout << "Jarvis: Learned the new response. Thank you!\n\n";
                continue; // Skip printing the bot's response for the newly learned expression
            }
        }
        cout << "Jarvis: " << bot_response << endl << endl;
    }

    return 0;
}
