#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Node structure
struct Song
{
    string title;
    string artist;
    string youtubeURL;

    Song *prev;
    Song *next;

    Song(string t, string a, string url)
    {
        title = t;
        artist = a;
        youtubeURL = url;

        prev = NULL;
        next = NULL;
    }
};

// Music Playlist Manager
class MusicPlaylist
{
private:
    Song *head;
    Song *tail;
    Song *current;

public:

    // Constructor
    MusicPlaylist()
    {
        head = NULL;
        tail = NULL;
        current = NULL;
    }

    // Add a song
    void addSong(string title, string artist, string url)
    {
        Song *newSong = new Song(title, artist, url);

        if (head == NULL)
        {
            head = newSong;
            tail = newSong;
            current = newSong;
        }
        else
        {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        cout << "\nSong added successfully!\n";
    }

    // Display playlist
    void displayPlaylist()
    {
        if (head == NULL)
        {
            cout << "\nPlaylist is empty!\n";
            return;
        }

        Song *temp = head;
        int count = 1;

        cout << "\n========== MUSIC PLAYLIST ==========\n";

        while (temp != NULL)
        {
            cout << count << ". "
                 << temp->title
                 << " - "
                 << temp->artist;

            if (temp == current)
            {
                cout << "  <-- Current Song";
            }

            cout << endl;

            temp = temp->next;
            count++;
        }

        cout << "====================================\n";
    }

    // Search song
    void searchSong(string title)
    {
        Song *temp = head;

        while (temp != NULL)
        {
            if (temp->title == title)
            {
                cout << "\nSong Found!\n";
                cout << "Title  : " << temp->title << endl;
                cout << "Artist : " << temp->artist << endl;
                cout << "YouTube: " << temp->youtubeURL << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "\nSong not found!\n";
    }

    // Open YouTube video
    void playCurrent()
    {
        if (current == NULL)
        {
            cout << "\nPlaylist is empty!\n";
            return;
        }

        cout << "\nOpening song on YouTube...\n";
        cout << "Title  : " << current->title << endl;
        cout << "Artist : " << current->artist << endl;

        // Windows command to open the URL
        string command =
            "start \"\" \"" + current->youtubeURL + "\"";

        int result = system(command.c_str());

        if (result != 0)
        {
            cout << "\nUnable to open the browser.\n";
        }
    }

    // Delete song
    void deleteSong(string title)
    {
        Song *temp = head;

        while (temp != NULL && temp->title != title)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "\nSong not found!\n";
            return;
        }

        // Update current song
        if (temp == current)
        {
            if (temp->next != NULL)
            {
                current = temp->next;
            }
            else
            {
                current = temp->prev;
            }
        }

        // Update previous node
        if (temp->prev != NULL)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next;
        }

        // Update next node
        if (temp->next != NULL)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev;
        }

        delete temp;

        if (head == NULL)
        {
            current = NULL;
        }

        cout << "\nSong deleted successfully!\n";
    }

    // Next song
    void nextSong()
    {
        if (current == NULL)
        {
            cout << "\nPlaylist is empty!\n";
            return;
        }

        if (current->next != NULL)
        {
            current = current->next;

            cout << "\nNext song selected!\n";
            playCurrent();
        }
        else
        {
            cout << "\nThis is the last song.\n";
        }
    }

    // Previous song
    void previousSong()
    {
        if (current == NULL)
        {
            cout << "\nPlaylist is empty!\n";
            return;
        }

        if (current->prev != NULL)
        {
            current = current->prev;

            cout << "\nPrevious song selected!\n";
            playCurrent();
        }
        else
        {
            cout << "\nThis is the first song.\n";
        }
    }

    // Count songs
    void countSongs()
    {
        int count = 0;
        Song *temp = head;

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        cout << "\nTotal Songs: " << count << endl;
    }

    // Clear playlist
    void clearPlaylist()
    {
        Song *temp = head;

        while (temp != NULL)
        {
            Song *nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }

        head = NULL;
        tail = NULL;
        current = NULL;

        cout << "\nPlaylist cleared successfully!\n";
    }

    // Destructor
    ~MusicPlaylist()
    {
        Song *temp = head;

        while (temp != NULL)
        {
            Song *nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }
    }
};

// Main function
int main()
{
    MusicPlaylist playlist;

    int choice;
    string title, artist, url;

    do
    {
        cout << "\n\n====================================";
        cout << "\n       MUSIC PLAYLIST MANAGER";
        cout << "\n====================================";
        cout << "\n1. Add Song";
        cout << "\n2. Delete Song";
        cout << "\n3. Search Song";
        cout << "\n4. Display Playlist";
        cout << "\n5. Play Current Song on YouTube";
        cout << "\n6. Next Song";
        cout << "\n7. Previous Song";
        cout << "\n8. Count Songs";
        cout << "\n9. Clear Playlist";
        cout << "\n10. Exit";
        cout << "\n====================================";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Enter a number.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice)
        {
            case 1:
                cout << "\nEnter Song Title: ";
                getline(cin, title);

                cout << "Enter Artist Name: ";
                getline(cin, artist);

                cout << "Enter YouTube Video URL: ";
                getline(cin, url);

                playlist.addSong(title, artist, url);
                break;

            case 2:
                cout << "\nEnter Song Title to Delete: ";
                getline(cin, title);

                playlist.deleteSong(title);
                break;

            case 3:
                cout << "\nEnter Song Title to Search: ";
                getline(cin, title);

                playlist.searchSong(title);
                break;

            case 4:
                playlist.displayPlaylist();
                break;

            case 5:
                playlist.playCurrent();
                break;

            case 6:
                playlist.nextSong();
                break;

            case 7:
                playlist.previousSong();
                break;

            case 8:
                playlist.countSongs();
                break;

            case 9:
                playlist.clearPlaylist();
                break;

            case 10:
                cout << "\nThank you for using Music Playlist Manager!\n";
                break;

            default:
                cout << "\nInvalid choice! Enter 1-10.\n";
        }

    } while (choice != 10);

    return 0;
}