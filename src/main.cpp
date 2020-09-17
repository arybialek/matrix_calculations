#include <iostream>
#include "../inc/matrix.h"
#include <stdexcept>

int menu()
{
    std::cout<<"\n\n---------- Main Menu: ----------"<<std::endl;
    std::cout<<"a - matrices multiplication"<<std::endl;
    std::cout<<"b - add matrices"<<std::endl;
    std::cout<<"c - calculate determinant"<<std::endl;
    std::cout<<"d - transpose a matrix"<<std::endl;
    std::cout<<"e - calculate a sum of elements"<< std::endl;
    std::cout<<"? - display menu again"<<std::endl;
    std::cout<<"q - exit"<<std::endl;
    return 0;
}

Matrix pathToMatrices(){
    Matrix matrix;
    std::string pathToMatrix;

    do{
        std::cout<<"\nPlease provide the absolute path to the file with the matrix: ";
        std::cin>>pathToMatrix;
        try{
            matrix.Load(pathToMatrix);
            return matrix;
        }catch(std::invalid_argument& e){
            std::cerr << "Incorrect path to the file: " << e.what() << std::endl;
        }
    }while(true);

}

int main(){
    char choice;
    std::string response;
    Matrix matrix1;
    Matrix matrix2;
    Matrix transposedMatrix1;
    Matrix addingResult;
    Matrix multiplicationResult;
    double sumOfElements;
    double determinant;

    std::cout<<"\n---------- Matrix Calculator ----------"<<std::endl;
    matrix1 = pathToMatrices();
    std::cout<<"\nWould you like to load the second matrix? (yes/no): ";
    std::cin>>response;
    if(response == "yes")
        matrix2 = pathToMatrices();

    menu(); // Display main menu.

    do{
        std::cout<<"\nWhat would you like to do? Write a correct character: ";
        std::cin>>choice;

        switch(choice)
        {

            case 'a':
                std::cout<<"\nYou have chosen matrices multiplication. Here's your result:"<<std::endl;
                try{
                    if(response=="yes"){
                        multiplicationResult = matrix1 * matrix2;
                        std::cout << multiplicationResult << std::endl;
                    }else{
                        std::cout << "You can't do multiplication while having only one matrix loaded." << std::endl;
                    }
                } catch (std::invalid_argument& e) {
                    std::cerr << "Something went wrong: " << e.what() << std::endl;
                }
                break;

            case 'b':
                std::cout<<"\nYou have chosen matrices addition. Here's your result:"<<std::endl;
                try{
                    if(response=="yes"){
                        addingResult = matrix1 + matrix2;
                        std::cout << addingResult << std::endl;
                    }else{
                        std::cout << "You can't add matrices while having only one matrix loaded." << std::endl;
                    }

                } catch (std::invalid_argument& e) {
                    std::cerr << "Something went wrong: " << e.what() << std::endl;
                }
                break;

            case 'c':
                std::cout<<"\nYou have chosen determinant calculation. "
                           "The first loaded matrix will be used to calculate it. "
                           "Here's your result:"<<std::endl;
                try{
                    determinant = matrix1.Determinant();
                    std::cout << determinant << std::endl;

                } catch (std::invalid_argument& e) {
                    std::cerr << "Something went wrong: " << e.what() << std::endl;
                }
                break;

            case 'd':
                std::cout<<"\nYou have chosen matrix transposition. "
                           "The first loaded matrix will be used to calculate it. "
                           "Here's your result:"<<std::endl;
                transposedMatrix1 = matrix1.Transpose();
                std::cout << transposedMatrix1 << std::endl;
                break;

            case 'e':
                std::cout<<"\nYou have chosen the sum of elements calculation. "
                           "The first loaded matrix will be used to calculate it. "
                           "Here's your result:"<<std::endl;
                sumOfElements = matrix1.SumOfElements();
                std::cout << sumOfElements << std::endl;
                break;

            case '?':
                menu();
                break;

            case 'q':
                std::cout<<"\nProgram terminated."<<std::endl;
                return 0;

            default:
                std::cout<<"\nIt seems that you have chosen an invalid option. Please try again."<<std::endl;
                break;
        }
    }while(choice!='q');

    return 0;
}
