#include "myWindow.h"
#include <gtkmm.h>
//#include <gtkmm/button.h>
//#include <gtkmm/filechoosernative.h>
//#include <gtkmm/entry.h>
#include <iostream>
#include <filesystem>

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& p_builder)
: Gtk::Window(cobject), m_builder{p_builder}
{
    Gtk::Button* p_button_open = nullptr; // Create a raw pointer to a button
    m_builder->get_widget("button_open", p_button_open); // Retrieve the button from XML file
    m_button_open = Glib::RefPtr<Gtk::Button>(p_button_open); // Assign to m_button


    Gtk::Button* p_button_read = nullptr; // Create a raw pointer to a button
    m_builder->get_widget("button_read", p_button_read); // Retrieve the button from XML file
    m_button_read = Glib::RefPtr<Gtk::Button>(p_button_read); // Assign to m_button



    Gtk::Button* p_button_proc = nullptr; // Create a raw pointer to a button
    m_builder->get_widget("button_proc", p_button_proc); // Retrieve the button from XML file
    m_button_proc = Glib::RefPtr<Gtk::Button>(p_button_proc); // Assign to m_button


    Gtk::Button* p_button_quit = nullptr; // Create a raw pointer to a button
    m_builder->get_widget("button_quit", p_button_quit); // Retrieve the button from XML file
    m_button_quit = Glib::RefPtr<Gtk::Button>(p_button_quit); // Assign to m_button


    Gtk::Entry* p_entry_file = nullptr; // Create a raw pointer to an entry field for input file
    m_builder->get_widget("entry_file", p_entry_file); // Retrieve the entry for input file
    m_entry_file = Glib::RefPtr<Gtk::Entry>(p_entry_file); // Assign to m_entry


    Gtk::Entry* p_entry_out_folder = nullptr; // Create a raw pointer to an entry field for out folder
    m_builder->get_widget("entry_out_folder", p_entry_out_folder); // Retrieve the entry for out folder
    m_entry_out_folder = Glib::RefPtr<Gtk::Entry>(p_entry_out_folder); // Assign to m_entry

    Gtk::Entry* p_entry_fps = nullptr; // Create a raw pointer to an entry field for fps value
    m_builder->get_widget("entry_fps", p_entry_fps); // Retrieve the entry for fps value
    m_entry_fps = Glib::RefPtr<Gtk::Entry>(p_entry_fps); // Assign to m_entry

    Gtk::Entry* p_entry_start = nullptr; // Create a raw pointer to an entry field for start value
    m_builder->get_widget("entry_start", p_entry_start); // Retrieve the entry for start value
    m_entry_start = Glib::RefPtr<Gtk::Entry>(p_entry_start); // Assign to m_entry

    Gtk::Entry* p_entry_end = nullptr; // Create a raw pointer to an entry field for stop value
    m_builder->get_widget("entry_end", p_entry_end); // Retrieve the entry for end value
    m_entry_end = Glib::RefPtr<Gtk::Entry>(p_entry_end); // Assign to m_entry



    // Connect the open button click event to the relative function
    m_button_open->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_select_input_clicked));

    // Connect the read button click event to the relative function
    m_button_read->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_read_button_clicked));

    // Connect the process button click event to the relative function
    m_button_proc->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_proc_button_clicked));

    // Connect the quit button click event to the relative function
    m_button_quit->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_quit_button_clicked));

}





void MainWindow::on_select_input_clicked()
{
    // Create a FileChooserNative dialog
    auto dialog = Gtk::FileChooserNative::create("Select a File", *this, Gtk::FILE_CHOOSER_ACTION_OPEN);

    // Show the dialog and wait for a response
    int result = dialog->run();

    // Handle the response
    if (result == Gtk::ResponseType::RESPONSE_ACCEPT)
    {
        auto filepath = dialog->get_filename();
        m_entry_file->set_text(filepath); // Set the entry text to the selected filepath


    // inizio inciarmo
    // contestualmente alla acquisizione dell'input file
    // tramite finestra di dialogo, viene anche scritto
    // il path della cartella di output

    std::filesystem::path filepath_fs = filepath;

    std::filesystem::path filename = filepath_fs.stem();

    std::filesystem::path parentpath_fs = filepath_fs.parent_path();

    std::filesystem::path outputFolder_fs = parentpath_fs / (filename.u8string() + "_frames");

    m_entry_out_folder->set_text(outputFolder_fs.u8string());

    // fine inciarmo


    }
}





void MainWindow::on_read_button_clicked()
{ /*function to read parameters from video file*/


    auto inputfile_path = m_entry_file->get_text();



    std::cout << inputfile_path.c_str() << std::endl;

    cv::VideoCapture vidcap = cv::VideoCapture(inputfile_path);
    int fps = vidcap.get(cv::CAP_PROP_FPS);

    int frameNumbers =  vidcap.get(cv::CAP_PROP_FRAME_COUNT);

    float durationSec =  (frameNumbers/fps) ;

    std::cout << "ftp = " << fps << std::endl;
    std::cout << "total frames = " << frameNumbers << std::endl;
    std::cout << "total duration (sec) = " << durationSec << std::endl;

    m_entry_fps->set_text(std::to_string(fps));

    m_entry_start->set_text(std::to_string(0));

    m_entry_end->set_text(std::to_string(durationSec));
}


void MainWindow::on_proc_button_clicked()
    { /*function to process video file*/

    auto inputfile_path = m_entry_file->get_text();

    std::cout <<"Processing file " << inputfile_path.c_str() << std::endl;


    //std::filesystem::path outputFolder_fs;  // create a variable

    Glib::ustring outputFolder = m_entry_out_folder->get_text();


    std::filesystem::path outputFolder_fs = std::string(outputFolder);

    outputFolder_fs = m_entry_out_folder->get_text();

    bool outputFolderExists = std::filesystem::is_directory(outputFolder_fs);


    if (not outputFolderExists)
    {

        bool create_success = std::filesystem::create_directories(outputFolder_fs);

        if (create_success)
        {
            std::cout <<"created output folder : " << outputFolder_fs.c_str() << std::endl;

        }
    }




    cv::VideoCapture vidcap = cv::VideoCapture(inputfile_path);



     if (!vidcap.isOpened())
        {
        std::cout <<"Cannot open the video file"<< std::endl;

        }


    double fps = vidcap.get(cv::CAP_PROP_FPS); //get the frames per seconds of the video

    int framesNumber =  vidcap.get(cv::CAP_PROP_FRAME_COUNT);

    int videoLengthMs = (framesNumber / fps) * 1000;


    float startMs = strtSec->value() * 1000 ;

    float endMs = endSec->value() * 1000;



    std::cout <<"framerate = " << fps << std::endl;
    std::cout <<"frames number = " << framesNumber << std::endl;
    std::cout <<"total duration (s) = " << (videoLengthMs/1000) << std::endl;


    int charnm = (std::to_string((int) (std::ceil(videoLengthMs)) )).length(); // number of characters needed for the
                                                            // longest timestamp here we need to typecast the result of
                                                              // "ceil" into an integer


    cv::Mat frame;

    bool bSuccess = vidcap.read(frame); // read a new frame from video

    int timestamp;
    std::stringstream ss;

    std::string outFilename;


    while(bSuccess)
    {

      timestamp = vidcap.get(cv::CAP_PROP_POS_MSEC);

      std::cout <<"read frame at timestamp  " + timestamp << std::endl;



    if (frame.empty())
        {
           std::cout <<"Reached last frame! " << std::endl;
           break;
        }


      outFilename = "";
      ss.str(std::string());


      ss << std::setfill('0') << std::setw(charnm) << timestamp;

      //ss << timestamp;

      outFilename = ss.str();

      outFilename.append(".png");

      bSuccess = vidcap.read(frame);

      std::filesystem::path outputFile_fs = outputFolder_fs / outFilename;

      cv::imwrite(outputFile_fs, frame);


      std::cout << "Saved frame  " <<  timestamp << std::endl;

    }


}







void MainWindow::on_quit_button_clicked()
{
this->close();
}
