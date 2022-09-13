#include "FileDialog.h"
#include <System/IO/Output.h>
#include <System/MemoryManagement.h>
#include <functional>
#include <gtk/gtk.h>

namespace Gum {
namespace Filesystem {
    void selectFileDialog(std::string defaultpath, ACTION action, std::function<void(std::string)> callback)
    {
        if (!gtk_init_check(NULL, NULL))
        {
            Gum::Output::error("GTK init failed");
            return;
        }

        GtkWidget* dialog = nullptr;
        if(action == ACTION::SAVE)
        {
            dialog = gtk_file_chooser_dialog_new("Save File", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL); 
            gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
        }
        else if(action == ACTION::OPEN)
        {
            dialog = gtk_file_chooser_dialog_new("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
        }

        /* Build the filter list */
        //AddFiltersToDialog(dialog, filterList);

        if(defaultpath != "")
            gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), defaultpath.c_str());

        if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        {
            std::string filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            if(filename == "")
            {
                gtk_widget_destroy(dialog);
                return;
            }
            callback(filename);
        }

        while (gtk_events_pending())
            gtk_main_iteration();
            
        gtk_widget_destroy(dialog);

        while (gtk_events_pending())
            gtk_main_iteration();
    }

    void selectMultipleFileDialog()
    {

    }

}};