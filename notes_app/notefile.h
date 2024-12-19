#ifndef NOTEFILE_H
#define NOTEFILE_H

#include <string>
#include <vector>
#include <mutex>

/*
* Represents a single note, which has both a title and some text content.
* Each NoteFile corresponds to a single file on disk and no two NoteFiles can
* be made  to correspond to the same file
*/
class NoteFile
{
public:
    /*
    * Constructs a new NoteFile, reading the title and contents from the file
    * located at file_path if it exists already (and writing a dummy file, if
    * not).  Throws if the file with path file_path is already in use by some
    * other NoteFile.
    */
    NoteFile(std::string file_path);

    ~NoteFile();

    /*
    * Updates the title of the note both in memory and on disk.
    */
    void UpdateTitle(std::string new_title);

    /*
    * Updates the contents of the note both in memory and on disk.
    */
    void UpdateContents(std::string new_contents);

    /*
    * Deletes the disk representation of the note.
    */
    void DeleteNoteFile();

private:
    /*
    * A vector of absolute file paths (as strings).
    * Used for ensuring that no NoteFile can be created with a file path that
    * already belongs to some other NoteFile.
    */
    static std::vector<std::string> file_paths_in_use;

    /*
    * Used to synchronize access to file_paths_in_use;
    */
    static std::mutex files_in_use_collection_mutex;

    /*
    * Corresponds to the first 256 characters of the text file backing this
    * note.
    */
    std::string title;

    /*
    * Corresponds to all characters after the first 256 in the underlying text
    * file representation.
    */
    std::string contents;

    /*
    * The absolute path to the underlying file.
    */
    std::string path;
};

#endif // NOTEFILE_H
