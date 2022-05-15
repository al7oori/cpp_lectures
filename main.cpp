#include <algorithm>
#include <ios>
#include <iostream>
#include <optional>
#include <vector>
#include <string>


constexpr auto MAX_ITEMS      = 30;
constexpr auto MAX_MODEL_NAME = 64;     

//enumeration class to list the items that the shop is selling

enum class Product
{
        Invalid = -1,
        vegetables,
        fruit,
        legumes,
        makeupproducts,
        spices,
        drugs,
        skincareproducts,
        dairyproducts,
        bottls,
        shampoo,
        Count //to check how many items are stored 
};

// stores the names of the items. //(CA, 3.4.2022)https://github.com/c2akula/cpp_lectures/blob/4add58c6acc595b622de7311fa8f60b44193d46e/main.cpp
constexpr std::string_view PRODUCT_NAMES[static_cast<int>(Product::Count)] = {
    [static_cast<int>(Product::vegetables)]         = "vegetables",
    [static_cast<int>(Product::fruit)]      = "fruit",
    [static_cast<int>(Product::legumes)]        = "legumes",
    [static_cast<int>(Product::makeupproducts)]  = "makeupproducts",
    [static_cast<int>(Product::spices)]     = "spices",
    [static_cast<int>(Product::drugs)]     = "drugs",
    [static_cast<int>(Product::skincareproducts)] = "skincareproducts",
    [static_cast<int>(Product::dairyproducts)]   = "dairyproducts",
    [static_cast<int>(Product::bottls)]      = "bottls",
    [static_cast<int>(Product::shampoo)] = "shampoo",
};


constexpr auto is_valid_product(Product prod) { return prod > Product::Invalid && prod < Product::Count; }


constexpr auto get_product_name(Product prod)
{
        if (!is_valid_product(prod)) { return std::string_view {""}; }

        return PRODUCT_NAMES[static_cast<int>(prod)];
}

// shows a list of types available.
auto list_products()
{
        std::cout << "Product list: \n";
        std::for_each_n(std::begin(PRODUCT_NAMES), std::size(PRODUCT_NAMES), [i = 0](const auto& name) mutable {
                std::printf("(%d) %s\n", i, name.data());
                i++;
        });
        std::printf("---------------\n");
}

// defining a struct for item and include properties in it
struct Item
{
        Product     id; // item id
        std::string name;  // name of the item
        std::string BestBeforeDate;  // date of expiry
        float       price;  // price of the product stored
        std::string type;   // type of the product stored
        int         nstock; //quantity of the chosen item

        Item() = default;

        Item(const Product prod, const std::string& name, const float price, const int nstock, const std::string& BestBeforeDate, std:: string& type) :
               id {prod}, name {name}, BestBeforeDate {BestBeforeDate}, price {price}, type {type}, nstock {nstock}
        {}
};


struct Inventory
{
        using SearchPredicate = std::function<bool(const Item&)>;
        using Items           = std::vector<Item>;
        using ItemPtr         = Items::iterator;     

        Items items;

        Inventory() { items.reserve(MAX_ITEMS); }

        // add item to the inventory.
        auto add(const Item& item) { items.emplace_back(item); }

        // delete item from the inventory.
        auto remove(ItemPtr pitem) { items.erase(pitem); }

        auto search(const SearchPredicate& pred) -> ItemPtr
        {
                auto pitem = std::find_if(items.begin(), items.end(), pred);
                if (pitem != items.end()) { return pitem; }

                return {};
        }
        // shows items that are already exist.
        auto list()
        {
                std::printf("%32s%64s%16s\n","name","type of item","Price (GBP)");
                std::for_each(items.begin(), items.end(), [](const auto& item) {
                std::printf("%32s%64s%16.2f%12d\n", get_product_name(item.id).data(), item.name.c_str(), item.price, item.nstock);
                });
                std::printf("---------------\n");
        }

       
};

struct InventoryUI //to create the interface for the user to interact with 
{
        enum class Option
        {
                Invalid      = -1,
                AddItem      = 'a',
                RemoveItem   = 'r',
                EditItem     = 'e',
                SearchItem   = 's',
                ListProducts = 'p',
                ListItems    = 'l',
                Quit         = 'q',
        };

        Inventory inventory;

        auto      user_input_handler() {}

        auto      list_options()
        {
                std::printf("(%c) Add Item\n", static_cast<char>(Option::AddItem));
                std::printf("(%c) Search Item\n", static_cast<char>(Option::SearchItem));
                std::printf("(%c) List Product Categories\n", static_cast<char>(Option::ListProducts));
                std::printf("(%c) List Items in Stock\n", static_cast<char>(Option::ListItems));
                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
        }

        auto get_user_action()
        {
                char opt {};
                std::printf("please select an operation to perform: ");
                std::scanf(" %c", &opt);
                return opt;
        }

        /// @brief Adds item to the inventory.
        auto handle_add_option()
        {
                Item item;
                do {
                        list_products();

                        std::printf("choose the type of the item you want to add: ");
                        int pid {};
                        std::scanf("%d", &item.id);

                        if (!is_valid_product(item.id)) { std::printf("somthing went wrong, please try again.\n"); }
                        else
                        {

                                std::printf("please enter item name: ");
                                std::getline(std::cin >> std::ws, item.name);

                                std::printf("please enter item price: ");
                                std::cin >> item.price;

                                std::printf("please enter item quantity: ");
                                std::cin >> item.nstock;


                                return item;
                        }

                } while (true);
        }

        /// @brief Search item by name or type to perform remove or edit operations on the found item.
        auto handle_search_option()
        {
                char opt {};
                std::printf("Search by (n) Name, (t) type: ");
                std::cin >> opt;

                Inventory::ItemPtr pitem;

                if (opt == 'n')
                {
                        // search for item by name
                        std::string name {};
                        std::printf("please enter item name name: ");
                        std::getline(std::cin >> std::ws, name);
                        pitem = inventory.search([&](const Item& item) { return item.name == name; });
                }
                else if (opt == 't')
                {
                        // search for item by type
                        std::string type {};
                        std::printf("please enter item type: ");
                        std::getline(std::cin >> std::ws, type);
                        pitem = inventory.search([&](const Item& item) { return item.type == type; });
                }        
                else
                {
                        std::printf("Invalid option selected. Please try again.\n");
                        return;
                }

                // if the item does exist
                if (pitem != Inventory::ItemPtr {})
                {
                        // operations to perform in the found item
                        do {
                                std::printf("(%c) Remove Item\n", static_cast<char>(Option::RemoveItem));
                                std::printf("(%c) Edit Item\n", static_cast<char>(Option::EditItem));
                                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
                                const auto opt = get_user_action();

                                if (opt == static_cast<char>(Option::RemoveItem))
                                {
                                        inventory.remove(pitem);
                                        break;
                                }
                                else if (opt == static_cast<char>(Option::EditItem))
                                {

                                        const auto new_item = handle_add_option();
                                        inventory.remove(pitem);
                                        inventory.add(new_item);
                                        break;
                                }
                                else if (opt == static_cast<char>(Option::Quit)) { break; }
                                else { std::printf("Invalid option selected. Please try again.\n"); }
                        } while (true);
                }
                else { std::printf("this item does not exist.\n"); }
        }

        auto run()
        {
                std::printf("Shop Inventory v0.1\n");

                do {
                        list_options();
                        const auto opt = get_user_action();
                        if (opt == static_cast<char>(Option::AddItem))
                        {
                                const auto item = handle_add_option();
                                inventory.add(item);
                                std::printf("Added item\n\n");
                        }
                        else if (opt == static_cast<char>(Option::SearchItem)) { handle_search_option(); }
                        else if (opt == static_cast<char>(Option::ListProducts)) { list_products(); }
                        else if (opt == static_cast<char>(Option::ListItems)) { inventory.list(); }
                        else if (opt == static_cast<char>(Option::Quit)) { break; }
                        else { std::printf("Invalid option selected. Please try again.\n"); }
                } while (true);
        }
};

auto main() -> int
{
        InventoryUI ui {};

        ui.run();
}