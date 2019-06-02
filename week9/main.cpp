//
// Created by Wojciech Ozimek on 02/06/2019.
//
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct MediaAsset
{
    virtual ~MediaAsset() = default; // make it polymorphic
};

struct Song : public MediaAsset
{
    std::wstring artist;
    std::wstring title;
    Song(const std::wstring& artist_, const std::wstring& title_) :
            artist{ artist_ }, title{ title_ } {
        wcout << "C-tor: artist " << artist << " title " << artist << endl;
    }
    ~Song() {
        wcout << "D-tor: artist " << artist << " title " << title << endl;
    }

};

struct Photo : public MediaAsset
{
    std::wstring date;
    std::wstring location;
    std::wstring subject;
    Photo(
            const std::wstring& date_,
            const std::wstring& location_,
            const std::wstring& subject_) :
            date{ date_ }, location{ location_ }, subject{ subject_ } {}
};

unique_ptr<Song> SongFactory(const std::wstring& artist, const std::wstring& title)
{
    // Implicit move operation into the variable that stores the result.
    return make_unique<Song>(artist, title);
}

void MakeSongs()
{
    // Create a new unique_ptr with a new object.
    auto song = make_unique<Song>(L"Mr. Children", L"Namonaki Uta");
    // Use the unique_ptr.
    vector<wstring> titles = { song->title };

    // Move raw pointer from one unique_ptr to another.
    unique_ptr<Song> song2 = std::move(song);

    // Obtain unique_ptr from function that returns by value.
    auto song3 = SongFactory(L"Michael Jackson", L"Beat It");
}

//3)
void SongVector()
{
    vector<unique_ptr<Song>> songs;

    // Create a few new unique_ptr<Song> instances
    // and add them to vector using implicit move semantics.
    songs.push_back(make_unique<Song>(L"B'z", L"Juice"));
    songs.push_back(make_unique<Song>(L"Namie Amuro", L"Funky Town"));
    songs.push_back(make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de"));
    songs.push_back(make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));

    // Pass by const reference when possible to avoid copying.
    for (const auto& song : songs)
    {
        wcout << L"Artist: " << song->artist << L"   Title: " << song->title << endl;
    }
}


int main() {

//    3)
    cout << "TASK 3" << endl << endl;

    cout << "Make songs" << endl;
    MakeSongs();
    cout << endl << endl << "Song Vector" << endl;
    SongVector();


//    5)
    cout << endl << "TASK 5" << endl << endl;

    auto sp1 = make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");
    cout << "Shared pointer ref counter: " << sp1.use_count() << endl;
    auto sp2(sp1); // copy c-tor
    cout << "Shared pointer ref counter: " << sp1.use_count() << endl;
    auto sp3 = sp2; // assignment
    cout << "Shared pointer ref counter: " << sp1.use_count() << endl;
}