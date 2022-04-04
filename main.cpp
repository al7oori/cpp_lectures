#include <algorithm>
#include <ios>
#include <iostream>
#include <optional>
#include <vector>
#include <string>



constexpr auto MAX_ITEMS      = 30;

//enumeration class to list the items that the shop is selling
enum class item
{
        Invalid = -1,
        vegetables,
        fruit,
        legumes,
        MakeupProducts,
        Spices,
        drugs,
        SkincareProducts,
        DairyProducts,
        bottls,
        shampoo,
        Count //to check how many items are stored 
};

/// stores the names of the items.
//(CA, 3.4.2022)https://github.com/c2akula/cpp_lectures/blob/4add58c6acc595b622de7311fa8f60b44193d46e/main.cpp

constexpr std::string_view ITEMS_NAMES[static_cast<int>(Item::Count)] = {
    [static_cast<int>(item::vegetables)]         = "vegetables",
    [static_cast<int>(item::fruit)]              = "fruit",
    [static_cast<int>(item::legumes)]           = "legumes",
    [static_cast<int>(item::MakeupProducts)]     = "MakeupProducts",
    [static_cast<int>(item::Spices)]             = "Spices",
    [static_cast<int>(item::drugs)]              = "drugs",
    [static_cast<int>(item::SkincareProducts)]   = "SkincareProducts",
    [static_cast<int>(item::DairyProducts)]      = "DairyProducts",
    [static_cast<int>(item::bottls)]             = "bottls",
    [static_cast<int>(item::shampoo)]           = "shampoo",
};
// defining a struct for item and include properties in it

struct item 
{
std::string Name; // name of the item
stdd::string BestBeforeDate; // date of expiry
float Price; // price of the product stored
std::string Type; // type of the product stored


};


struct inventory
{
    std::vector<item> items(10) {"vegetables, fruit, legumes, MakeupProducts, Spices, drugs, SkincareProducts, DairyProducts, bottls, shampoo"}
    items - all zero 

//(CA, 3.4.2022)https://github.com/c2akula/cpp_lectures/blob/4add58c6acc595b622de7311fa8f60b44193d46e/main.cpp
        /// Adds the given item to the inventory.
        auto add_item( Item const& item)-> bool
         { items.emplace_back(Item)
         return true;
         }

        ///  Delete the given item from the inventory.
        auto remove_item(ItemPtr pitem) 
        { items.erase(pitem)
         return true;
        }

        auto find_item()-> void
        {
        }

        ///  searching for an item.
        auto search(const SearchPredicate& pred) -> ItemPtr
        {
                auto pitem = std::find_if(items.begin(), items.end(), pred);
                if (pitem != items.end()) { return pitem; }

                return {};
        }


};

struct InventoryUI //to create the interface for the user to interact with 
{

int main()
{
        std::printf("shop inventory\n");
        std::printf("Press 'a' for adding an item\n");
        std::printf("Press 'r' for removing and item\n");
        std::printf("Press 's' for searching for an item\n");
        std::printf("Press 'e' for editing an item\n");
        
        // Escape Characters
        char opt = '\0'; // NUL character or 0
        std::scanf(" %c", &opt);
        return opt;



        switch (opt)
        {
                case 'a':
                case 'r':
                case 's':
                case 'e':

                break;
                default:
                        std::printf("Invalid option!\n");
                        return -1;
        }

    

        switch (opt)
        {
            //(CA, 3.4.2022)https://github.com/c2akula/cpp_lectures/blob/4add58c6acc595b622de7311fa8f60b44193d46e/main.cpp
                case 'a':
                        auto handle_add_option()
        {
                Item item;
                do {
                        list_products();

                        std::printf("select the item you want to add: ");
                        int pid {};
                        std::scanf("%d", &item.id);

                        if (!is_valid_product(item.id)) { std::printf("Invalid option selected. Please try again.\n"); }
                        else
                        {
                            
                                std::printf("Enter the item name: ");
                                std::getline(std::cin >> std::ws, item.name);

                                std::printf("Enter price: ");
                                std::cin >> item.price;

                                std::printf("Enter the best before date: ");
                                std::cin >> item.BestBeforeDate

                                std::printf("Enter price: ");
                                std::cin >> item.price;


                                return item;
                        }

                } while (true);
        }
                        break;
               /* case 'r':
                        break;*/
                case 's':
                             std::string name {};
                        std::printf("Enter item name: ");
                        std::getline(std::cin >> std::ws, name);
                        pitem = inventory.search([&](const item& item) { return item.name == name; });
                        break;
               /* case 'e':
                    
                        break;*/

        }


};



auto main() -> int
{
        InventoryUI ui {};

        ui.run();
}
},