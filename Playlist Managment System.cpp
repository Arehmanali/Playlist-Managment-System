
#include <cstring>
#include<fstream>
using namespace std;

class Song
{
	// output the song in the format:
	// title, artist
	friend ostream& operator<<(ostream& os, const Song& song);

	// input the song in the format:
	// title, artist
	friend istream& operator>>(istream& is, Song& song);

	// compare two song objects for equality
	friend bool operator==(const Song& lhs, const Song& rhs);

public:
	// constructors
	Song();
	Song(const char* t, const char* a);

	// set the song
	void Set(const char* t, const char* a);

private:
	static const int MAX_CHARS = 64;
	char title[MAX_CHARS];
	char artist[MAX_CHARS];
};
class Playlist {
	friend Playlist operator +(const Playlist& p1, Song& s2)
	{
		Playlist p2;
		cout << "Enter the title of song and artist (title,artist) to add in playlist :";
		cin >> s2;
		p2 = p1;
		p2.plist[p2.numOfSongs] = s2;								//input a song in song array
		p2.numOfSongs++;
		cout << "Song has been added succesfuly\n";
		p2.doubleSize();
		return p2;
	}
	friend Playlist operator -(Playlist& p1,Song& s2)
	{
		Playlist p;
		p = p1;
		bool a = false;
		cout << "Enter the name of song to delete from playlist :";																		//Object of Song to campare from Song array
		cin >> s2;
		int i;
		for (i = 0; i < p.numOfSongs; i++)
		{
			if (p.plist[i] == s2)													//Compare song from song array
			{
				a = true;
				break;
			}
		}
		if (a == true)
		{
			p.plist[i] = p.plist[i + 1];
			p.numOfSongs--;
			cout << "Song has been Deleted successfully\n";
			p.halfSize();
		}
		else
		{
			cout << "Song has NOT been deleted successfully\n";
		}
		return p;
	}
public:

	Playlist();							//Constructor

	void AddSong(Song& s2);			//Add song in playlist
	bool DeleteSong(Song& s2);			//delete song from playlist
	void ShowAll()const;					//show the detail of song 
	void Play(int num);					//play song from playlist
	void ShowStatus()const;					//show the status of song
	void doubleSize();						//double the size of array of song
	void halfSize();						//Reduce the siz of array of song
	~Playlist();							//Destructor

private:
	int arraySize;
	int numOfSongs;
	int indexOfSong;
	Song* plist = new Song[arraySize];		//Dynamic allocated song array 

};
void handleInputfailure()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
	}
}
Playlist::Playlist()
{
	arraySize = 2;
	numOfSongs = 0;
	indexOfSong = 0;
	plist[arraySize];						//Create a song array of size 2
}
void Playlist::AddSong(Song& s2)
{
	cout << "Enter the title of song and artist (title,artist) to add in playlist :";
	cin >> s2;
	plist[numOfSongs] = s2;																	//input a song in song array
	numOfSongs++;
	cout << "Song has been added succesfuly\n";
	doubleSize();
	handleInputfailure();
}
bool Playlist::DeleteSong(Song& s2)
{
	bool a = false;
	cout << "Enter the name of song to delete from playlist :";																		//Object of Song to campare from Song array
	cin >> s2;
	int i;
	for (i = 0; i < numOfSongs; i++)
	{
		if (plist[i] == s2)													//Compare song from song array
		{
			a = true;
			break;
		}
	}
	if (a == true)
	{
		plist[i] = plist[i + 1];
		numOfSongs--;
		cout << "Song has been Deleted successfully\n";
		halfSize();
	}
	else
	{
		cout << "Song has NOT been deleted successfully\n";
	}
	handleInputfailure();
	return true;
}
void Playlist::ShowAll()const
{
	cout << "\n Song Detail:\n";
	for (int i = 0; i < numOfSongs; i++)
	{
		cout << plist[i] << endl;
	}
}
void Playlist::Play(int num)
{
	int next;
	if (numOfSongs == 0)						//to check empty playlist
	{
		cout << "Your Playlist is Empty. Please Add Song.\n";
	}
	for (num; num < numOfSongs; num++)
	{
		do {
			cout << "Now Song is Playing :" << plist[num] << endl;
			indexOfSong = num;
			if (num + 1 < numOfSongs)
			{
				cout << "The Next Song is :" << plist[num + 1] << endl;
				cout << "Enter '1' for Next Song to Play and '0' to Exit :";
				cin >> next;
			}
			else
			{
				cout << "Playlist Have No More Song.\n";
				break;
			}
		} while (next != 1);

	}
	handleInputfailure();
}
void Playlist::ShowStatus()const
{
	cout << "The Size of Song Array is :" << arraySize << endl;
	cout << "The Total Number of Songs in Playlist are :" << numOfSongs << endl;
	cout << "The Current Index of Song is :" << indexOfSong << endl;
}
void Playlist::doubleSize()
{
	if (arraySize <= numOfSongs)
	{
		arraySize = arraySize * 2;
	}
}
void Playlist::halfSize()
{
	if (numOfSongs / 2 <= arraySize)
	{
		arraySize = arraySize / 2;
	}
}
Playlist::~Playlist()
{
	delete[]plist;				//Deallocate the song array
}
void IgnoreNewLines()
{
	while (cin.peek() == '\n')
		cin.ignore();
}

// default constructor
Song::Song()
{
	strcpy_s(title, "");
	strcpy_s(artist, "");
}

Song::Song(const char* t, const char* a)
{
	Set(t, a);
}

void Song::Set(const char* t, const char* a)
{
	if (strlen(t) < MAX_CHARS)
		strcpy_s(title, t);

	if (strlen(a) < MAX_CHARS)
		strcpy_s(artist, a);
}

// output operator
ostream& operator<<(ostream & os, const Song & song)
{
	os << song.title << ", " << song.artist;
	return os;
}

// input operator
istream& operator>>(istream & is, Song & song)
{
	// ignore any newlines
	IgnoreNewLines();

	// read until the comma
	cin.getline(song.title, Song::MAX_CHARS, ',');

	// ignore the space in between
	if (cin.peek() == ' ')
		cin.ignore();

	// ignore any newlines
	IgnoreNewLines();

	// read until new line
	cin.getline(song.artist, Song::MAX_CHARS, '\n');
	handleInputfailure();
	return is;
}

// equality test operator
bool operator==(const Song & lhs, const Song & rhs)
{
	if (strcmp(lhs.title, rhs.title))
		return false;

	if (strcmp(lhs.artist, rhs.artist))
		return false;
	return true;
}

int main()
{
	Song s2;				//Object of Song class
	Playlist p1;			//object of playlist class
	int option;

lable1:
	cout << "\n******Wellcome to Song playlist******\n";
	cout << "Please select from following:\n";
	cout << "1.	Play Songs\n";
	cout << "2.	Add Songs\n";
	cout << "3.	View All Songs\n";
	cout << "4.	Delete Songs\n";
	cout << "5.	Show Status\n";
	cout << "6.	Exist From Playlist\n";
	cout << "Choose an option:";
	cin >> option;
	switch (option)
	{
	case 1:
		p1.Play(0);
		goto lable1;
		break;
	case 2:
		p1.AddSong(s2);
		goto lable1;
		break;
	case 3:
		p1.ShowAll();
		goto lable1;
		break;
	case 4:
		p1.DeleteSong(s2);
		goto lable1;
		break;
	case 5:
		p1.ShowStatus();
		goto lable1;
		break;
	case 6:
		break;
	default:
		cout << "Your input is INVALID. Please try again\n";
		goto lable1;
		break;
	}
	handleInputfailure();
	return 0;
}
