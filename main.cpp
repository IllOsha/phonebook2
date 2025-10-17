#include <iostream>
#include <fstream>
#include "phonebook.h"
#include "validators.h"
#include <limits>

int main() {
    phonebook pb;
    const std::string datafile = "phonebook.db";
    
    std::ifstream test(datafile);
    if (!test.good()) {
        std::ofstream create(datafile);
        if (create) {
            create.close();
            std::cout << "created new data file: " << datafile << "\n";
        } else {
            std::cerr << "error  cannot create data file.\n";
            return 1;
        }
    }

    pb.loadfromfile(datafile);
    std::cout << "loaded " << pb.size() << " contacts.\n";

    while (true) {
        std::cout << "commands: list, add, find, delete, save, stats, exit\n> ";
        std::string cmd;
        if (!(std::cin >> cmd)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (cmd == "list") {
            pb.listall();
        }
        else if (cmd == "add") {
            contacts d;
            std::string tmp;

            std::cout << "FIRST NAME: ";
            std::getline(std::cin, d.firstname);
            std::cout << "LAST NAME: ";
            std::getline(std::cin, d.lastname);
            std::cout << "MIDDLE NAME: ";
            std::getline(std::cin, d.middlename);
            std::cout << "EMAIL: ";
            std::getline(std::cin, d.email);
            std::cout << "BIRTHDAY DD-MM-YYYY: ";
            std::getline(std::cin, d.birthday);
            std::cout << "ADDRESS: ";
            std::getline(std::cin, d.address);

            while (true) {
                std::cout << "add number? (y/n): ";
                std::string a;
                std::getline(std::cin, a);
                if (a == "n" || a == "N") break;
                if (a.empty()) continue;

                PhoneNumber p;
                std::cout << "label: ";
                std::getline(std::cin, p.label);
                std::cout << "number: ";
                std::getline(std::cin, p.number);
                if (!Validators::validphone(p.number))
                    std::cout << "warning: invalid phone format.\n";
                d.phones.push_back(p);
            }

            if (!Validators::validname(d.firstname) || !Validators::validname(d.lastname)) {
                std::cout << "invalid name — not added.\n";
            } else {
                pb.addcontact(std::move(d));
                std::cout << "added.\n";
            }
        }
        else if (cmd == "find") {
            std::string q;
            std::cout << "Enter search query: ";
            std::getline(std::cin, q);
            auto res = pb.findbyname(q);
            if (res.empty()) std::cout << "no contacts found.\n";
            else {
                for (auto idx : res) {
                    const auto &c = pb.at(idx);
                    std::cout << "[" << idx << "] " << c.lastname << " "
                              << c.firstname << " | " << c.email << "\n";
                }
            }
        }
        else if (cmd == "delete") {
            std::cout << "enter index to delete: ";
            size_t idx;
            std::cin >> idx;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (pb.removebyindex(idx)) std::cout << "removed.\n";
            else std::cout << "invalid index.\n";
        }
        else if (cmd == "save") {
            if (pb.savetofile(datafile))
                std::cout << "saved.\n";
            else
                std::cout << "could not save.\n";
        }
        else if (cmd == "stats") {
            std::cout << "total contacts: " << pb.size() << "\n";
        }
        else if (cmd == "exit") {
            pb.savetofile(datafile);
            std::cout << "goodbye\n";
            break;
        }
        else {
            std::cout << "unknown command u re not a human\n";
        }
    }

    return 0;
}
