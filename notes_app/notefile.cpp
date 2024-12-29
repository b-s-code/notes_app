#include "notefile.h"
#include <string>
#include <QFile>

std::mutex NoteFile::files_in_use_collection_mutex;
std::vector<std::string> NoteFile::file_paths_in_use;

NoteFile::NoteFile(std::string file_path)
{
    {
        std::scoped_lock<std::mutex> lock(files_in_use_collection_mutex);

        for (const std::string& path : NoteFile::file_paths_in_use)
        {
            if (file_path == path)
            {
                throw; // TODO : throw something specific?
            }
        }

        // It is now confirmed that file_path does not correspond to any file
        // already belonging to another NoteFile.  So either read the file's
        // contents, checking if they're of an appropriate length, or create the
        // file if it does not already exist.
        if (!QFile::exists(QString::fromStdString(file_path)))
        {
            auto open_mode_RW_text = QIODeviceBase::ReadWrite
                                     | QIODeviceBase::Text;
            file.setFileName(QString::fromStdString(file_path));
            file.open(open_mode_RW_text);

            // Default title is a placeholder string, then padded up to 256
            // characters with spaces.  Default contents is simply empty.
            std::string default_title = "Untitled";

            title = default_title;
            default_title += "                                                                                                                                                                                                                                                        ";
            file.write(default_title.c_str());
        }
        else
        {
            // The file apparently exists.

            std::string title_and_contents = file.readAll().toStdString();

            std::string title_from_file = title_and_contents.substr(0, 256);
            std::string contents_from_file = title_and_contents.substr(256);

            title = title_from_file;
            contents = contents_from_file;
        }
    }
}

NoteFile::~NoteFile()
{
    file.close();
}

void NoteFile::UpdateTitle(std::string new_title)
{
    // TODO : update both memory and disk rep's.

    // TODO : add a method which:
    // - checks input string is no longer than 256 characters, and
    // - returns a new string which consists in the input string, padded up to
    //   256 characters with spaces.
    // Some existing code could reuse this method.
}

void NoteFile::UpdateContents(std::string new_contents)
{
    // TODO : update both memory and disk rep's.
}

void NoteFile::DeleteNoteFile()
{
    {
        std::scoped_lock lock {NoteFile::files_in_use_collection_mutex};
        // TODO :
        // - Remove file from disk.
        // - Update file_paths_in_use.
    }
}
