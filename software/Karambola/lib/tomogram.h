#ifndef TOMOGRAM 
#define TOMOGRAM

#include <assert.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <stdint.h>

//#if defined(_M_X64) || defined(__amd64__)
//typedef SIZETYPE uint64_t;
//#else
//typedef SIZETYPE uint32_t;
//#endif




template <typename VALUE>
class tomogram3d{
    public:
    void initialise(int a,int b,int c, VALUE value){
        sx = a;
        sy = b;
        sz = c;
        data.resize(sx*sy*sz);
        for (unsigned int i = 0; i < sx*sy*sz; ++i){
            data.at(i) = value;
        }
    }
    
    void clear(){
        data.clear();
        sx = 0;
        sy = 0;
        sz = 0;
    }

    int get_sx() const { return sx;}
    int get_sy() const { return sy;}
    int get_sz() const { return sz;}

    
    VALUE get (unsigned int x, unsigned int y, unsigned int z) const{
        unsigned int pos = (x + y*sx + z*sx*sy);
        return data.at(pos);
    }

    void set (unsigned int x, unsigned int y, unsigned int z, VALUE value){
        unsigned int pos = (x + y*sx + z*sx*sy);
        data.at(pos) = value;
    }

    VALUE find_max() const{
        VALUE maxvalue = *std::max_element (data.begin(),data.end());
        return maxvalue;
    }

    void write_hist (std::string outfilename) const{
        std::cout << "creating hist ... " << std::flush;
        int binsinhist = int(find_max());
        std::vector <int> hist (binsinhist+1,0);
        for (unsigned int k = 0; k != sz; ++k)
            for (unsigned int j = 0; j != sy; ++j)
                for (unsigned int i = 0; i != sx; ++i){
                    hist.at(int(get(i,j,k))) += 1;
                }
        std::cout << " done" << std::endl;
        std::cout << "write " << outfilename << " ... " << std::flush;
        std::ofstream histfile;
        histfile.open (outfilename.c_str());
        for (int i = 0; i < binsinhist; i++){
            histfile << i << " " << hist.at(i) << std::endl;
        }
        histfile.close();
        std::cout << " done" << std::endl;
    }
    void write_hist_inside (std::string outfilename) const{
        std::cout << "creating hist inside ... " << std::flush;
        int binsinhist = int(find_max());
        std::vector <int> hist (binsinhist+1,0);
        for (unsigned int k = 0; k != sz; ++k)
            for (unsigned int j = 0; j != sy; ++j)
                for (unsigned int i = 0; i != sx; ++i){
                    if(k < 10 || k > sz - 10) continue;
                    double r = sqrt(pow(abs(i-(sx/2)),2)+pow(abs(j-(sy/2)),2));
                    if(r<(sx/2)-50){
                        hist.at(int(get(i,j,k))) += 1;
                    }
                }
        std::cout << " done" << std::endl;
        std::cout << "write " << outfilename << " ... " << std::flush;
        std::ofstream histfile;
        histfile.open (outfilename.c_str());
        for (int i = 0; i < binsinhist; i++){
            histfile << i << " " << hist.at(i) << std::endl;
        }
        histfile.close();
        std::cout << " done" << std::endl;
    }
    std::vector<double> calc_hist_radial_range (double r_min, double r_max, std::string outfilename) const{
        std::cout << "creating hist range: " << r_min << " - " << r_max << std::flush;
        int binsinhist = int(find_max());
//        std::vector <double> hist (static_cast<int>(binsinhist/10.) +1,0);
        std::vector <double> hist (binsinhist +1,0);
        unsigned int number_of_values = 0;
        for (unsigned int k = 0; k != sz; ++k)
            for (unsigned int j = 0; j != sy; ++j)
                for (unsigned int i = 0; i != sx; ++i){
                    if(k < 10 || k > sz - 10) continue;
                    double r = sqrt(pow(abs(i-(sx/2)),2)+pow(abs(j-(sy/2)),2));
                    if(r > r_min && r < r_max){
//                        hist.at(int(get(i,j,k)/10.)) += 1;
                        hist.at(int(get(i,j,k))) += 1;
                        number_of_values++;
                    }
                }
        for (unsigned int i = 0; i < hist.size(); i++){
            hist.at(i) = hist.at(i)/(static_cast<double> (number_of_values));
        }
        std::cout << " done" << std::endl;
        std::cout << "write " << outfilename << " ... " << std::flush;
        std::ofstream histfile;
        histfile.open (outfilename.c_str());
        for (unsigned int i = 0; i < hist.size(); i++){
            histfile << i << " " << hist.at(i) << std::endl;
        }
        histfile.close();
        std::cout << " done" << std::endl;
        return hist;
    }  
    void write_raw (std::string outfilename, std::string type) const{
        std::cout << "write " << outfilename << " ... " << std::flush;
        std::ofstream outfile;
        outfile.open(outfilename.c_str());
//        outfile.write ((char*)&data[0], sizeof (VALUE)*data.size());

        if (type == "uint8_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                uint8_t number;
                if (data.at(i) < 0 || fabs(data.at(i)) > std::numeric_limits<uint8_t>::max())
                    throw std::runtime_error ("Cant't write file: Numbers are to big for selected class type");
                number = uint8_t(data.at(i));
                outfile.write ((char *)&number,sizeof (number));
            }
        }

        else if (type == "uint16_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                uint16_t number;
                if (data.at(i) < 0 || fabs(data.at(i)) > std::numeric_limits<uint16_t>::max())
                    throw std::runtime_error ("Cant't write file: Numbers are to big for selected class type");
                number = uint16_t(data.at(i));
                outfile.write ((char *)&number,sizeof (number));
            }
        }

        else if (type == "uint32_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                uint32_t number;
                if (data.at(i) < 0 || fabs(data.at(i)) > std::numeric_limits<uint32_t>::max())
                    throw std::runtime_error ("Cant't write file: Numbers are to big for selected class type");
                number = uint32_t(data.at(i));
                outfile.write ((char *)&number,sizeof (number));
            }
        }

        else if (type == "int"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                int number;
                if (data.at(i) > std::numeric_limits<int>::max())
                    throw std::runtime_error ("Cant't write file: Numbers are to big for selected class type");
                number = int(data.at(i));
                outfile.write ((char *)&number,sizeof (number));
            }
        }
        else{
            throw std::runtime_error ("can't write raw type");
        }

        outfile.close();
        std::cout << " done" << std::endl;
    }

    void write_pgm (std::string outfilename, int picnumber) const{
        std::cout << "write " << outfilename << " ... " << std::flush;
        std::ofstream myfile;
        myfile.open (outfilename.c_str());
        myfile << "P2" << std::endl;
        myfile << sx << " " << sy << std::endl;
        
        VALUE maxvalue = *std::max_element (data.begin()+(picnumber*sx*sy),data.begin()+((picnumber+1)*sx*sy));

        myfile << int(maxvalue) << std::endl;
        for (unsigned int j = 0; j != sy; ++j)
            for (unsigned int i = 0; i != sx; ++i){
                myfile << int(get(i,j,picnumber)) << std::endl;
            }
        myfile.close();
        std::cout << " done" << std::endl;
    }

#if 0
    void readfile (std::string infilename, int a, int b, int c){
        sx = a;
        sy = b;
        sz = c;
        int npixel = sx*sy;
        int npic = sz;
        data.resize(sx*sy*sz);

        std::ifstream infile;
        infile.open(infilename.c_str());
        infile.read ((char *)&data[0],sizeof (VALUE) * npixel*npic);
        infile.close();
    }
#endif

    void read_raw (std::string infilename, std::string type, int a, int b, int c){
        sx = a;
        sy = b;
        sz = c;
        data.resize(sx*sy*sz);

        std::ifstream infile;
        infile.open(infilename.c_str());

        if (type == "uint8_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                uint8_t number;
                infile.read ((char *)&number,sizeof (number));
                if (number > std::numeric_limits<VALUE>::max())
                    throw std::runtime_error ("Can't read file: Numbers are to big for selected class type");
                data.at(i) = VALUE(number);
            }
        }
        else if (type == "uint16_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                uint16_t number;
                infile.read ((char *)&number,sizeof (number));
                if (number > std::numeric_limits<VALUE>::max())
                    throw std::runtime_error ("Can't read file: Numbers are to big for selected class type");
                data.at(i) = VALUE(number);
            }
        }
        else if (type == "int32_t"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                int32_t number;
                infile.read ((char *)&number,sizeof (number));
                if (number > std::numeric_limits<VALUE>::max())
                    throw std::runtime_error ("Can't read file: Numbers are to big for selected class type");
                data.at(i) = VALUE(number);
            }
        }
        else if (type == "int"){
            for (unsigned int i = 0; i<sx*sy*sz; i++){
                int number;
                infile.read ((char *)&number,sizeof (number));
                if (number > std::numeric_limits<VALUE>::max())
                    throw std::runtime_error ("Can't read file: Numbers are to big for selected class type");
                data.at(i) = VALUE(number);
            }
        }
        else{
            throw std::runtime_error ("can't read raw type");
        }

        infile.close();
    }

    void read_bin (std::string infilename){
        std::cout << "reading " << infilename << " ... " << std::flush;        
        std::ifstream ifile;
        ifile.open(infilename.c_str());
        ifile >> sx >> sy >> sz;
        data.resize(sx*sy*sz);

        for (unsigned int i = 0; i < sx*sy*sz; i++){
            for(;;){
                int c = ifile.get();
                switch (c) {
                    case EOF:
                        std::cerr << "end of file while reading structure";
                        abort ();
                    case '\n':
                    case ' ':
                    case '\t':
                        // ignore
                        continue;
                    default:
                        int x = c - '0';
                        if (x < 0 || x > 10) {
                            std::cerr << "invalid character in file: "
                                << (char)(c) << "\n";
                            abort ();
                        }
                        data.at(i)= (VALUE) x;
                }
                break;
            }
        }
        ifile.close();
        std::cout << " done" << std::endl;        
    }

    private:
    std::vector <VALUE> data;
    unsigned int sx,sy,sz;
};



#endif // TOMOGRAM
