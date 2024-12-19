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
            auto f = QFile(); // TODO : make this a member variable and close it
                              // in destructor.  Or implement something else.
            auto open_mode_RW_text = QIODeviceBase::ReadWrite
                                     | QIODeviceBase::Text;
            f.setFileName(QString::fromStdString(file_path));
            f.open(open_mode_RW_text);

            // TODO : write default title, padded up to 256 characters (consider
            // whether want to use UTF-8 or UTF-16, noting that I may want to
            // alternately use std::string/QString).  Leave contents empty.

        }
        else
        {
            // TODO : read title and contents.
        }

    }
}

void NoteFile::UpdateTitle(std::string new_title)
{
    // TODO : update both memory and disk rep's.
}

void NoteFile::UpdateContents(std::string new_contents)
{
    // TODO : update both memory and disk rep's.
}

void NoteFile::DeleteNoteFile()
{
    {
        std::scoped_lock lock{NoteFile::files_in_use_collection_mutex};
        // TODO :
        // - Remove file from disk.
        // - Update file_paths_in_use.
    }
}
