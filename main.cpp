switch (dashboardChoice)
{
case 1:
    vault.addPasswordFromInput();
    break;

case 2:
    vault.viewPasswords();
    break;

case 3:
    cout << "\nSearch Password (Coming Soon)\n";
    break;

case 4:
    cout << "\nEdit Password (Coming Soon)\n";
    break;

case 5:
    cout << "\nDelete Password (Coming Soon)\n";
    break;

case 6:
    cout << "\nLogged Out Successfully.\n";
    break;

default:
    cout << "\nInvalid Choice.\n";
}