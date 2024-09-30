#pragma once

#include <gtkmm.h>
//#include <gtkmm/builder.h>
//#include <gtkmm/button.h>
//#include <gtkmm/entry.h>
//#include <gtkmm/filechoosernative.h>
//#include <gtkmm/label.h>

#include <opencv2/opencv.hpp>

#include <opencv2/core.hpp>
//#include <videoio/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <string>

#include <filesystem>


class MainWindow : public Gtk::Window
{
public:
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& p_builder);

protected:
    Glib::RefPtr<Gtk::Builder> m_builder;

    Glib::RefPtr<Gtk::Button> m_button_open;


    Glib::RefPtr<Gtk::Button> m_button_read;    // read parameters

    Glib::RefPtr<Gtk::Button> m_button_proc;  //processing

    Glib::RefPtr<Gtk::Entry> m_entry_file;
    Glib::RefPtr<Gtk::Entry> m_entry_out_folder;


    Glib::RefPtr<Gtk::Entry> m_entry_fps;
    Glib::RefPtr<Gtk::Entry> m_entry_start;
    Glib::RefPtr<Gtk::Entry> m_entry_end;


    Glib::RefPtr<Gtk::Button> m_button_quit;





    // Signal handler:
    void on_select_input_clicked();

    void on_read_button_clicked();

    void on_proc_button_clicked();

    void on_quit_button_clicked();
};
