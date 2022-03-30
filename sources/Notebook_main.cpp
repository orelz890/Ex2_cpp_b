// #include "Notebook.hpp"

// using ariel::Direction;
// using ariel::Notebook;


// // How to run: g++ -o a.out Notebook.cpp Notebook_main.cpp Notebook.hpp
// namespace ariel{
//     void print_ans(Notebook& n, int action){
//         int page, row, col, d, len;
//         string w;
//         Direction direction;
//         if (action > 0 && action < 4){
//             cout<< "Enter a page, row, col, direction - {Horizental = 1, else 2}\n";
//             cin>> page>> row >> col>> d;
//             fflush(stdin);
//             if (d == 1){
//                 direction = Direction::Horizontal;
//             }
//             else{
//                 direction = Direction::Vertical;
//             }
//         }
//         switch (action)
//         {
//         case 1:
//             cout<< "Enter a string to write\n";
//             cin>> w;
//             n.write(page,row,col,direction, w);
//             break;
//         case 2:
//             cout<< "Enter a length to read\n";
//             cin>> len;
//             cout << n.read(page,row,col,direction, len);
//             break;
//         case 3:
//             cout<< "Enter a length to erase\n";
//             cin>> len;
//             n.erase(page,row,col,direction, len);
//             break;
//         case 4:
//             cout<< "Enter a page to show\n";
//             cin>> page;
//             n.show(page);
//             break;
//         default:
//             cout<< "The input isn't legal\n";
//             break;
//         }
//     }
// }

// int main(){
//     Notebook n;
//     int action = -1;
//     while (1){
//         cout<<"\nEnter an action number:/n Exit(notebook will be deleted!) = 0, Write = 1 , Read = 2, Erase = 3, Show = 4\n"<<endl;
//         cin>>action;
//         fflush(stdin);
//         if (action == 0){
//             cout<< "Goodbye my friend\n";
//             break;
//         }
//         ariel::print_ans(n, action);

//     }

//     return 0;
// }
