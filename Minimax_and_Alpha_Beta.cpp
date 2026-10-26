#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <cctype>

using namespace std;





void clearScreen()
{
#ifdef _WIN32
    clearScreen();
#else
    cout << "\n\n\n";   // no screen wipe, so the AI's move stays visible
#endif
}

void pauseScreen()
{
#ifdef _WIN32
    pauseScreen();
#endif
}

void drawBoard(string state);

string play(string state, bool xturn);
string playAI(string state, bool xturn);
string playAIab(string state, bool xturn);


int minimax(string state, bool xturn);
double minvalue(string state, int& move);
double maxvalue(string state, int& move);

int minimaxAB(string state, bool xturn);
double minvalueAB(string state, double alpha, double beta, int& move);
double maxvalueAB(string state, double alpha, double beta, int& move);

int eval(string state);  //given a state s, return 1 if x wins, -1 if o wins, 0  undetermined (may or may not be a leaf)




int main()
{
	string state;
	bool xturn;
	
	cout << "Testing eval function ...\n";
	pauseScreen();

	string s[] = { ".........", "o..xooxXx","xoxxoxoO.", "x.oxOxo..","......xox","xxooxxoxo",".x..o...x" };

	for (int i = 0; i < 7; i++)
	{
		clearScreen();
		drawBoard(s[i]);
		cout << "Evaluation : " << eval(s[i]) << endl;
		pauseScreen();
	}


	cout << "Testing minimax by game playing ...\n";
	pauseScreen();


	//AI goes first
	state = ".........";
	drawBoard(state);
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAI(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}

	pauseScreen();
	xturn = true;
	state = ".........";

	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAI(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	pauseScreen();




	cout << "Testing minimax alpha-beta by game playing ...\n";
	pauseScreen();



	//AI goes first
	state = ".........";
	drawBoard(state);
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAIab(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}

	pauseScreen();
	xturn = true;
	state = ".........";

	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAIab(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}

	pauseScreen();
	return 0;
}


/********************************************************/
///Drawing and game play functions////////////////////////
void drawBoard(string state)
{
	string board[] = { ".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....", };
	cout << endl;

	for (int i = 0; i < 9; i++)
	{
		int a = i / 3, b = i % 3;
		board[a * 4 + 1][b * 6 + 2] = state[i];
	}

	cout << "      0     1     2" << endl;
	cout << endl;

	for (int i = 0; i < 11; i++)
	{
		if (i % 4 == 1)
			cout << i / 4 << "   ";
		else
			cout << "    ";
		for (int j = 0; j < 17; j++)
		{
			char ch = toupper(board[i][j]);
			switch (ch)
			{
			case '.': cout << ' '; break;
			case '|': cout << '|'; break;
			case '-': cout << '-'; break;
			case '+': cout << '+'; break;
			case 'X': cout << 'X'; break;
			case 'O': cout << 'O'; break;
			}

		}
		cout << endl;
	}
	cout << endl;
}

string play(string state, bool xturn)
{
	int r, c;
	clearScreen();
	drawBoard(state);
	if (xturn)
	{
		cout << "X-player, enter the coordinates of where you want to play (row then column):";
		cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' || state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'x';
	}
	else
	{
		cout << "O-player, enter the coordinates of where you want to play (row then column):";
		cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' || state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'o';
	}
	clearScreen();
	drawBoard(state);
	return state;
}

string playAI(string state, bool xturn)
{
	int action = minimax(state, xturn);// assign action based on algorithm

	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	clearScreen();
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	pauseScreen();
	return state;
}

string playAIab(string state, bool xturn)
{
	int action = minimaxAB(state, xturn);// assign action based on algorithm

	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	clearScreen();
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	pauseScreen();
	return state;
}


int minimax(string state, bool xturn)
{
	double val;
	int action;
	for (int i = 0; i < 9; i++)
		state[i] = tolower(state[i]);

	if (xturn)  //max players turn
		val = maxvalue(state, action);
	else
		val = minvalue(state, action);
	return action;
}


///Algorighm functions

int eval(string state)
// given a state s, return 1 if x wins, -1 if o wins, 0  undetermined (may or may not be a leaf)
{
    // converting the string to all lowercase
    for (int z = 0; z < state.size(); z++)
    {
        state[z] = (char)tolower(state[z]);
    }
    // intializing vectors to check
    vector<int> row1 = {0, 1, 2};
    if (state[0] == state[1] && state[1] == state[2])
    {
        if (state[0] == 'x')
        {
            return 1;
        }
        else if (state[0] == 'o')
        {
            return -1;
        }
    }
    vector<int> row2 = {3, 4, 5};
    if (state[3] == state[4] && state[3] == state[5])
    {
        if (state[3] == 'x')
        {
            return 1;
        }
        else if (state[3] == 'o')
        {
            return -1;
        }
    }
    vector<int> row3 = {6, 7, 8};
    if (state[6] == state[7] && state[6] == state[8])
    {
        if (state[6] == 'x')
        {
            return 1;
        }
        else if (state[6] == 'o')
        {
            return -1;
        }
    }
    vector<int> column1 = {0, 3, 6};
    if (state[0] == state[3] && state[0] == state[6])
    {
        if (state[0] == 'x')
        {
            return 1;
        }
        else if (state[0] == 'o')
        {
            return -1;
        }
    }
    vector<int> column2 = {1, 4, 7};
    if (state[4] == state[1] && state[1] == state[7])
    {
        if (state[1] == 'x')
        {
            return 1;
        }
        else if (state[1] == 'o')
        {
            return -1;
        }
    }
    vector<int> column3 = {2, 5, 8};
    if (state[2] == state[5] && state[2] == state[8])
    {
        if (state[2] == 'x')
        {
            return 1;
        }
        else if (state[2] == 'o')
        {
            return -1;
        }
    }
    vector<int> diagonal1 = {0, 4, 8};
    if (state[0] == state[4] && state[0] == state[8])
    {
        if (state[0] == 'x')
        {
            return 1;
        }
        else if (state[0] == 'o')
        {
            return -1;
        }
    }
    vector<int> diagonal2 = {2, 4, 6};
    if (state[2] == state[4] && state[2] == state[6])
    {
        if (state[2] == 'x')
        {
            return 1;
        }
        else if (state[2] == 'o')
        {
            return -1;
        }
    }
    return 0;
}

double minvalue(string state, int &move)
{
    // calling the eval to see if its terminal
    if (eval(state) != 0 || state.find('.') == string::npos)
    {
        return eval(state);
    }
    double v = 100000;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == '.')
        {
            string state2 = state;
            state2[i] = 'o';
            int a2;
            double v2 = maxvalue(state2, a2);
            if (v2 < v)
            {
                v = v2;
                move = i;
            }
        }
    }
    return v;
}


double maxvalue(string state, int &move)
{
    // cout << state << endl;
    // calling the eval to see if its terminal
    if (eval(state) != 0 || state.find('.') == string::npos)
    {
        return eval(state);
    }
    double v = -10000;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == '.')
        {
            string state2 = state;
            state2[i] = 'x';
            int a2;
            double v2 = minvalue(state2, a2);
            if (v2 > v)
            {
                v = v2;
                move = i;
            }
        }
    }
    return v;
}


int minimaxAB(string state, bool xturn)
{
    double val;
    int action = -1;
    int InfinityNegative = -10000;
    int InfinityPositive = 10000;
    for (int i = 0; i < 9; i++)
        state[i] = tolower(state[i]);
    if (xturn) // max players turn
        val = maxvalueAB(state, InfinityNegative, InfinityPositive, action);
    else
        val = minvalueAB(state, InfinityNegative, InfinityPositive, action);
    return action;
}



double minvalueAB(string state, double alpha, double beta, int &move)
{
    // calling the eval to see if its terminal
    if (eval(state) != 0 || state.find('.') == string::npos)
    {
        return eval(state);
    }
    double v = 100000;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == '.')
        {
            string state2 = state;
            state2[i] = 'o';
            int a2;
            double v2 = maxvalueAB(state2, alpha, beta, a2);
            if (v2 < v)
            {
                v = v2;
                move = i;
                beta = min(beta, v);
            }
            if (v <= alpha)
            {
                move = i;
                return v;
            }
        }
    }
    return v;
}

double maxvalueAB(string state, double alpha, double beta, int &move)
{
    // cout << state << endl;
    // calling the eval to see if its terminal
    if (eval(state) != 0 || state.find('.') == string::npos)
    {
        return eval(state);
    }
    double v = -10000;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == '.')
        {
            string state2 = state;
            state2[i] = 'x';
            int a2;
            double v2 = minvalueAB(state2, alpha, beta, a2);
            if (v2 > v)
            {
                v = v2;
                move = i;
                alpha = max(alpha, v);
            }
            if (v >= beta)
            {
                move = i;
                return v;
            }
        }
    }
    return v;
}
