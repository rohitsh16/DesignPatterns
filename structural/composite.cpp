#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class FileSystemObject {
public:
    virtual ~FileSystemObject() = default;
    virtual void show(int indent = 0) const = 0;
};

class File : public FileSystemObject {
public:
    File(const string& name) : name(name) {}

    void show(int indent = 0) const override {
        cout << string(indent, ' ') << "- File: " << name << "\n";
    }

private:
    string name;
};

class Folder : public FileSystemObject {
public:
    Folder(const string& name) : name(name) {}

    void add(shared_ptr<FileSystemObject> item) {
        contents.push_back(move(item));
    }

    void show(int indent = 0) const override {
        cout << string(indent, ' ') << "+ Folder: " << name << "\n";
        for (const auto& item : contents) {
            item->show(indent + 2); // indent children
        }
    }

private:
    string name;
    vector<shared_ptr<FileSystemObject>> contents;
};

int main() {
    auto root = make_shared<Folder>("Root");

    // Add files
    root->add(make_shared<File>("file1.txt"));
    root->add(make_shared<File>("file2.txt"));

    // Create subfolder
    auto subFolder = make_shared<Folder>("Documents");
    subFolder->add(make_shared<File>("doc1.pdf"));
    subFolder->add(make_shared<File>("doc2.pdf"));

    // Add subfolder to root
    root->add(subFolder);

    root->show();
    return 0;
}

/*
Composite Pattern Summary:

1. Treat individual (leaf) and group (composite) objects the same way.
2. Perfect for hierarchical data — file systems, UIs, trees, etc.
3. Promotes recursive structures and clean APIs.

Key Parts:
- Component        => `FileSystemObject`
- Leaf             => `File`
- Composite        => `Folder`
- Client           => `main()`
*/
