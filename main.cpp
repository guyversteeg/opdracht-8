// Name / student number / study student 1 : Guy Versteeg / 4378857 / Informatica
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

struct Length
{
	int minutes;							// #minuten  (0..)
	int seconds;							// #seconden (0..59)
};

struct Track
{
	string artist;                          // naam van uitvoerende artiest
	string cd;                              // titel van cd
	int    year;                            // jaar van uitgave
	int    track;							// nummer van track
	string title;                           // titel van track
	string tags;                            // tags van track
	Length time;							// lengte van track
	string country;                         // land van artiest
};

struct TrackDisplay
{
	bool showArtist;						// toont artist als true
	bool showAlbum;							// toont cd titel als true
	bool showYear;							// toont year als true
	bool showTrack;							// toont track nr als true
	bool showTitle;							// toont track titel als true
	bool showTags;                          // toont tags als true
	bool showLength;						// toont track lengte als true
	bool showCountry;                       // toont country als true
};

bool match (string sub, string source)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    Resultaat is true alleen als sub een letterlijke (case-sensitive) deelstring is van source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length lengte)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    de waarde van lengte is getoond via out in de vorm: minuten, ':', seconden (tenminste 2 digits)
*/
    cout << lengte.minutes << " : " << lengte.seconds;
    return out;
}

istream& operator>> (istream& in, Length& lengte)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    de waarde van lengte is ingelezen uit in: eerst minuten, daarna ':', daarna seconden.
*/
    int minutes = 0;
    int seconds = 0;
    in >> minutes;
    if (in.get() != ':')
        return in;
    if (in)
    {
        lengte.minutes = minutes;
        lengte.seconds = seconds;
    }
    return in;
}

Length operator+ (const Length& a, const Length& b)
{// Preconditie:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postconditie:
    Resultaat is de som van a en b.
*/
    Length lengte;
    lengte.minutes = a.minutes + b.minutes + (a.seconds + b.seconds) / 60;
    lengte.seconds = (a.seconds + b.seconds) % 60;
    return lengte;
}

void show_track (Track lied,TrackDisplay lt)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    alleen die members van lied zijn getoond waarvan de corresponderende member in lt de waarde true heeft.
*/
    if(lt.showArtist)
    {
        cout << "Artist:  " << lied.artist << endl;
    }
    if(lt.showAlbum)
    {
        cout << "Album:   " << lied.cd << endl;
    }
    if(lt.showYear)
    {
            cout << "Year:    " << lied.year << endl;
    }
    if(lt.showTrack)
    {
        cout << "Track:   " << lied.track << endl;
    }
    if(lt.showTitle)
    {
        cout << "Title:   " << lied.title << endl;
    }
    if(lt.showTags)
    {
        cout << "Tags:    " << lied.tags << endl;
    }
    if(lt.showLength)
    {
        cout << "Length:  " << lied.time << endl;
    }
    if(lt.showCountry)
    {
        cout << "Country: " << lied.country << endl;
    }
}

void endline(istream& instream)
{
//  Preconditie:
    assert (true);
/*
    Postconditie:
    Loopt de regel af, totdat /n tegenkomt en gaat naar de volgende regel.
*/
    while (instream && instream.get() != '\n');
}

istream& operator>> (istream& in, Track& track)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    De inhoud van de eerstvolgende 8 regels uit in zijn gelezen en omgezet naar de corresponderende members in track.
    De daaropvolgende (lege) regel uit in is ook gelezen.
*/
    getline(in, track.artist);
    getline(in, track.cd);
    in >> track.year;
    endline(in);
    in >> track.track;
    endline(in);
    getline(in, track.title);
    getline(in, track.tags);
    in >> track.time;
    endline(in);
    getline(in, track.country);
    endline(in);
    return in;
}

const int MAX_NR_OF_TRACKS = 5000;
typedef Track MusicDB [MAX_NR_OF_TRACKS];

int main()
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    De muziekdatabase "Nummers.txt" is (indien aanwezig en correct geformateerd) ingelezen.
    De gebruiker is in staat geweest database queries te stellen en heeft de antwoorden op deze
    queries gezien.
*/
	return 0;
}
