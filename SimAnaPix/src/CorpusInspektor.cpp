#include "CorpusInspektor.hpp"

// Get files of input folder:
void CorpusInspektor::read_corpus()
{
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(shrd->source_folder.c_str())) == NULL)
    {
        std::cout << "Error(" << errno << ") opening " << shrd->source_folder << std::endl;
    }

    const std::string srce_fldr_path = shrd->source_folder;
    const char *chr_srce_fldr_path = srce_fldr_path.c_str();

    while ((dirp = readdir(dp)) != NULL)
    {
        if (((std::string("README")).compare(dirp->d_name) != 0) && ((std::string(".")).compare(dirp->d_name) != 0) && ((std::string("..")).compare(dirp->d_name) != 0))
        {
            std::cout << "Found " << dirp->d_name << std::endl;
            // Magick::Image local_file_image(source_folder + "/" + dirp->d_name);
            // if (check_format(local_file_image) == true)
            // {
            char newname[800];
            strcpy(newname, "01_possible_corpus/");
            std::strcat(newname, dirp->d_name);
            std::cout << "newname before pushback! " << newname << std::endl;
            shrd->image_files.push_back(std::string(newname));

            // }
            // else
            // {
            // 	std::cout << source_folder + "/" + dirp->d_name << " has wrong format" << std::endl;
            // 	moveFileTo(dirp->d_name, source_folder, reject_folder);
            // 	char newname[800];
            // 	strcpy(newname, "wrong_format_");
            // 	std::strcat(newname, dirp->d_name);
            // 	rename_file(dirp->d_name, reject_folder, newname);
            // }
        }
    }
    closedir(dp);
    std::cout << "Number of files in possible corpus: " << shrd->image_files.size() << std::endl;
    return;
}

void CorpusInspektor::load_images(){

    ofTexture act_img;
    for(int i=0; i<(shrd->image_files.size());i++){
        cout<< "Load Image "<< shrd->image_files[i]<< endl;
        ofLoadImage(act_img, shrd->image_files[i]);
        shrd->image_database.push_back(act_img);
        cout << "added to Database. " << endl;
    }
    cout << "Database has now " << shrd->image_database.size() << "Loaded Images " << endl;

    return;
}

void CorpusInspektor::set_actl_image(int it){
    if((it >= 0)&&(it < shrd->image_database.size())){
        shrd->actl_img = shrd->image_database[it];
        shrd->prev_img = shrd->image_database[it];
    }
    else{
        cout<< "iterator has stackoverflow"  <<endl;
    }
    return;
}


// bool Corpus_Inspektor::check_format(Magick::Image Image_)
// {
//     //  std::cout <<"filterout_bad_format()"<<"\n";
//     std::vector<std::string> lossless_formats;
//     lossless_formats.push_back("BMP");
//     lossless_formats.push_back("PNG");
//     lossless_formats.push_back("ARW");
//     for (auto i : lossless_formats)
//     {
//         if (i == Image_.magick())
//         {
//             return true;
//         }
//     }
//     return false;
// }