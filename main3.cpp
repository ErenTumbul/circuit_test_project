#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <istream>
#include <vector>

#include <algorithm>
using namespace std;

// dosya adý manuel giriliyor

vector<string> parser(string& str, const string& delim)
{

    vector<string> tokens;

    int tokenStart = 0;

    int delimPos = str.find_first_of(delim);

    while(delimPos != string::npos)
    {
        string tok = str.substr(tokenStart, delimPos - tokenStart);



        tokens.push_back(tok);

        delimPos = str.find_first_not_of(delim, delimPos +1);

        tokenStart = delimPos;

        delimPos = str.find_first_of(delim, delimPos);
    }



    return tokens;

}

string merg(string str1,string str2,const string& delim)//önce üstüne yazýlacak olan
{

    vector<string> line1,line2;
    line1=parser(str1,delim);
    line2=parser(str2,delim);
    string s;



    line1.insert(line1.end(),line2.begin(),line2.end());

    s=line1[0]+" ";


    for(int j=1;j<line1.size();j++)
    {

        if(j == line1.size()-1)
        {
            s += line1[j]+";";
        }
        else
        {
            s += line1[j]+",";
        }
    }

    return s;

}

string module(string module,string out_dff,string in_dff, const string& delim)
{

    string s,y;
    vector<string> pline,pline1,pline2;

    pline = parser(module,delim);
    pline1 = parser(out_dff,delim);
    pline2 = parser(in_dff,delim);


    pline1.insert(pline1.end(),pline2.begin(),pline2.end());

    for(int j=0;j<pline1.size();j++)
    {

        if(j!=pline1.size()-1)
        {
           y += pline1[j]+",";
        }
        else
        {
           y += pline1[j];
        }
    }




    s = pline[0] + " " + pline[1] + "(";

    for(int i=2;i<pline.size();++i)
    {
        s+=pline[i]+", ";
    }

    s+=y + ");";

    return s;

}


void dosyaya_yaz(string module,string input,string output,string wire,const string& delims)
{
    fstream file,file2;
    string line;
    vector<string> pline;

     file.open("benchfile.txt",ios::in | ios::out);

    if(!file.is_open())
    {
        cout<<"could not reached the file!"<<endl;
    }
    else
    {
        file2.open("newbenchfile38.v",ios::in | ios::out | ios::app | ios::binary);

        while(!file.eof())
        {

            getline(file,line);
            pline = parser(line,delims);
            int s=pline.size();
            bool x=false;

            for(int i=0;i<s;i++)
            {

                if(pline[i]=="module" && pline[i+1]=="dff")
                {
                   while(x==false)
                   {
                       if(line=="endmodule")
                       {
                           x=true;
                       }
                       else
                       {
                           getline(file,line);
                       }
                   }
                }
                else if(pline[i]=="module" && pline[i+1]!="dff")
                {
                    while(x==false)
                    {
                         if(line.find(';') != std::string::npos)
                         {
                             cout<<module<<endl;
                             file2<<module<<endl<<endl;
                             x=true;
                         }
                         else if(line.find(';') == std::string::npos)
                         {
                             getline(file,line);
                         }
                    }
                }
                else if(pline[i]=="input")
                {

                     while(x==false)
                    {
                         if(line.find(';') != std::string::npos)
                         {
                             cout<<input<<endl;
                             file2<<input<<endl<<endl;
                             x=true;

                         }
                         else if(line.find(';') == std::string::npos)
                         {
                             getline(file,line);
                         }
                    }
                }
                else if(pline[i]=="output")
                {

                    while(x==false)
                    {
                         if(line.find(';') != std::string::npos)
                         {
                             file2<<output<<endl<<endl;
                             cout<<output<<endl;
                             x=true;

                         }
                         else if(line.find(';') == std::string::npos)
                         {
                             getline(file,line);
                         }
                    }
                }
                else if(pline[i]=="wire")
                {

                     while(x==false)
                    {
                         if(line.find(';') != std::string::npos)
                         {
                             file2<<wire<<endl<<endl;
                             cout<<wire<<endl;
                             x=true;

                         }
                         else if(line.find(';') == std::string::npos)
                         {
                             getline(file,line);
                         }
                    }
                }
                else if(pline[1]=="dff")
                {
                   continue;
                }
                else if(pline[0]!="module" && pline[0]!="input" && pline[0]!="output" && pline[i]!="wire")
                {
                    file2<<line<<endl<<endl;
                    cout<<line<<endl;
                    break;
                }

            }


            }

        }
    file.close();
    file2.close();

}



int main()
{


    fstream file,file2;
    string line;
    vector<string> pline,pline1;

    string const delims = ",(){}; ";
    string arr_module;
    string arr_input;
    string arr_output;
    string arr_wire;
    string outputs_dff;
    string inputs_dff;
    string arr_input2;
    string arr_output2,module_last;




    file.open("benchfile.txt",ios::in | ios::out);

    if(!file.is_open())
    {
        cout<<"could not reached the file!"<<endl;
    }

    else
    {

        while(!file.eof())
        {
            getline(file,line);
            pline = parser(line,delims);
            int s=pline.size();
            string line1,mline;
            bool k = false;


            for(int i=0;i<s;i++)
            {
                  if(pline[i]=="module")
                  {
                      while(k==false)
                        {
                            if(line.find(';') != std::string::npos)
                            {
                               mline=mline+line;
                               k=true;
                            }
                            else if(line.find(';') == std::string::npos)
                            {
                                mline=mline+line;
                                getline(file,line);
                            }
                        }
                        ;
                        arr_module = mline;
                  }
                  else if(pline[i]=="input")
                  {

                      while(k==false)
                        {
                            if(line.find(';') != std::string::npos)
                            {
                               mline=mline+line;
                               k=true;
                            }
                            else if(line.find(';') == std::string::npos)
                            {
                                mline=mline+line;
                                getline(file,line);
                            }
                        }
                        arr_input=mline;
                  }
                  else if(pline[i]=="output")
                  {
                      while(k==false)
                        {
                            if(line.find(';') != std::string::npos)
                            {
                               mline=mline+line;
                               k=true;
                            }
                            else if(line.find(';') == std::string::npos)
                            {
                                mline=mline+line;
                                getline(file,line);
                            }
                        }
                        arr_output=mline;
                  }
                  else if(pline[i]=="wire")
                  {
                      while(k==false)
                        {
                            if(line.find(';') != std::string::npos)
                            {
                               mline=mline+line;
                               k=true;
                            }
                            else if(line.find(';') == std::string::npos)
                            {
                                mline=mline+line;
                                getline(file,line);
                            }
                        }
                        arr_wire=mline;
                 }
                 else if(pline[i]=="dff" && pline[i-1]!="module")
                 {
                     outputs_dff = outputs_dff+pline[4]+",";
                     inputs_dff=inputs_dff+pline[5]+",";
                 }
            }
           }


    }

    string arr_input2;
    string arr_output2,module_last;
    arr_input2 = merg(arr_input,inputs_dff,delims);
    arr_output2 = merg(arr_output,outputs_dff,delims);
    module_last = module(arr_module,outputs_dff,inputs_dff,delims);


    file.close();


    dosyaya_yaz(module_last,arr_input2,arr_output2,arr_wire,delims);


 return 0;
}
