#include <iostream>
#include <string>
#include <memory>

using namespace std;

class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const string& audioType, const string& fileName) = 0;
};

class AdvancedMediaPlayer {
public:
    void playVLC(const string& fileName) {
        cout << "Playing VLC file: " << fileName << endl;
    }

    void playMP4(const string& fileName) {
        cout << "Playing MP4 file: " << fileName << endl;
    }
};

class MediaAdapter : public MediaPlayer {
public:
    MediaAdapter(const string& audioType) {
        player = make_unique<AdvancedMediaPlayer>();
        this->audioType = audioType;
    }

    void play(const string& audioType, const string& fileName) override {
        if (audioType == "vlc") {
            player->playVLC(fileName);
        } else if (audioType == "mp4") {
            player->playMP4(fileName);
        } else {
            cout << "Unsupported format in adapter.\n";
        }
    }

private:
    unique_ptr<AdvancedMediaPlayer> player;
    string audioType;
};

class AudioPlayer : public MediaPlayer {
public:
    void play(const string& audioType, const string& fileName) override {
        if (audioType == "mp3") { // existing legacy support
            cout << "Playing MP3 file: " << fileName << endl;
        } else if (audioType == "vlc" || audioType == "mp4") { // new feat support
            MediaAdapter adapter(audioType);
            adapter.play(audioType, fileName);
        } else {
            cout << "Invalid media format: " << audioType << endl;
        }
    }
};

int main() {
    unique_ptr<MediaPlayer> player = make_unique<AudioPlayer>();

    player->play("mp3", "song.mp3");
    player->play("vlc", "movie.vlc");
    player->play("mp4", "clip.mp4");
    player->play("avi", "unknown.avi");

    return 0;
}

/*
Adapter Pattern Summary:

1. Translates one interface into another.
2. Useful when integrating legacy or third-party code.
3. Promotes reusability without modifying existing code.

Components:
- Target Interface   => `MediaPlayer`
- Adaptee            => `AdvancedMediaPlayer`
- Adapter            => `MediaAdapter`
- Concrete Target    => `AudioPlayer`
- Client             => `main()`

Real-World Uses:
- UI widgets bridging different frameworks
- Network or protocol converters
*/
