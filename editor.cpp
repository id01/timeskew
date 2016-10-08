#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtkmm.h>
#define SKEWF 0
#define SKEWD 1

// Gtk mains
int gtkmainf(int argc, char * argv[]);
int gtkmaind(int argc, char * argv[]);
void incrementf();
void decrementf();

// Function to change skew
void changeskew(int num, int denom)
{
	printf("%d, %d\n", num, denom);
	FILE* tsf=fopen("/tmp/.timeskew","w");
	if (tsf)
	{
		fprintf(tsf, "%i %i", num, denom);
		fclose(tsf);
	}
}

// Function to invoke changeskew with dec input
void changeskewd(Gtk::Entry * numEntry, Gtk::Entry * denomEntry)
{
	int num = atoi(numEntry->get_text().c_str());
	int denom = atoi(denomEntry->get_text().c_str());
	changeskew(num, denom);
}

// Function to invoke changeskew with float input
void changeskewf(Gtk::Entry * inputEntry)
{
	float skewamount = atof(inputEntry->get_text().c_str());
	changeskew(skewamount*1000, 1000);
}

int main(int argc, char *argv[])
{
// *****
// INIT SECTOR
// *****
	// Fool the system
	int fauxargc = 0;

	// Declare numerator, denominator, and float.
	int num; int denom;
	float skewamount;
	// If syntax error.
	if (argc==1) { return 0; }
	// Get mode.
	int mode=atoi(argv[1]);
	// Check if timeskew file is openable
	FILE* tsf=fopen("/tmp/.timeskew","w");
	if (tsf)
	{
		printf("Opened /tmp/.timeskew. Starting!\n");
		fclose(tsf);
	}
	else
	{
		printf("Unable to open /tmp/.timeskew. Do you have sufficient permissions?\n"); return 2;
	}
	if (mode==SKEWF) { return gtkmainf(fauxargc, argv); }
	if (mode==SKEWD) { return gtkmaind(fauxargc, argv); }
}

// Gtk main (float version)
int gtkmainf(int argc, char * argv[])
{
// *****
// GTK BUILD SECTOR
// *****
	// Create app
	auto app = Gtk::Application::create(argc, argv, "hi.hi.hi");

	// Create window, set default size and border width
	Gtk::Window myWindow;
	myWindow.set_title("Timeskew Editor");
	myWindow.set_default_size(256,64);
	myWindow.set_border_width(10);

	// Create default grid
	Gtk::Grid defaultGrid;
	
	// Create mode label
	Gtk::Label modeLabel;
	modeLabel.set_text("Timeskew Editor: Float Mode");

	// Create input entry
	Gtk::Entry inputEntry;
	inputEntry.set_editable(TRUE);
	inputEntry.signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::ptr_fun(&changeskewf), &inputEntry));

	// Create entry label
	Gtk::Label entryLabel; entryLabel.set_text("Decimal: ");
	
	// Create buttons grid
	Gtk::Grid buttonsGrid;
	
	// Create submit button
	Gtk::Button submitButton("Submit");
	submitButton.set_size_request(120, 0);
	submitButton.signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::ptr_fun(&changeskewf), &inputEntry));

	// Create increment and decrement buttons
	Gtk::Button decrementButton("   <<   ");
	decrementButton.signal_clicked().connect(sigc::ptr_fun(&decrementf));
	Gtk::Button incrementButton("   >>   ");
	incrementButton.signal_clicked().connect(sigc::ptr_fun(&incrementf));

// *****
// GTK DRAW SECTOR
// *****
	// Attatch items to grid, attach grid to window.
	defaultGrid.attach(modeLabel, 0, 0, 2, 1);
	defaultGrid.attach(entryLabel, 0, 1, 1, 1);
	defaultGrid.attach(inputEntry, 1, 1, 1, 1);
	buttonsGrid.add(decrementButton);
	buttonsGrid.add(submitButton);
	buttonsGrid.add(incrementButton);
	defaultGrid.attach(buttonsGrid, 0, 2, 4, 1);
	myWindow.add(defaultGrid);

	// Show everything
	modeLabel.show();
	inputEntry.show();
	incrementButton.show();
	submitButton.show();
	decrementButton.show();
	entryLabel.show();
	buttonsGrid.show();
	defaultGrid.show();

	// Start main loop
	return app->run(myWindow);
}

// Gtk main (dec version)
int gtkmaind(int argc, char * argv[])
{
// *****
// GTK BUILD SECTOR
// *****
	// Create app
	auto app = Gtk::Application::create(argc, argv, "hi.hi.hi");

	// Create window, set default size and border width
	Gtk::Window myWindow;
	myWindow.set_title("Timeskew Editor");
	myWindow.set_default_size(256,64);
	myWindow.set_border_width(10);

	// Create default grid
	Gtk::Grid defaultGrid;
	
	// Create mode label
	Gtk::Label modeLabel;
	modeLabel.set_text("Timeskew Editor: Fraction Mode");

	// Create input entrys
	Gtk::Entry numEntry;
	numEntry.set_editable(TRUE);
	Gtk::Entry denomEntry;
	denomEntry.set_editable(TRUE);
	numEntry.signal_activate().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::ptr_fun(&changeskewd), &numEntry, &denomEntry));
	denomEntry.signal_activate().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::ptr_fun(&changeskewd), &numEntry, &denomEntry));
	
	// Create input entry labels
	Gtk::Label fracLabel; fracLabel.set_text("Fraction: ");
	Gtk::Label slashLabel; slashLabel.set_text(" / ");

	// Create submit button
	Gtk::Button submitButton("Submit");
	submitButton.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::ptr_fun(&changeskewd), &numEntry, &denomEntry));

// *****
// GTK DRAW SECTOR
// *****
	// Attatch items to grid, attach grid to window.
	defaultGrid.attach(modeLabel, 0, 0, 4, 1);
	defaultGrid.attach(fracLabel, 0, 1, 1, 1);
	defaultGrid.attach(numEntry, 1, 1, 1, 1);
	defaultGrid.attach(slashLabel, 2, 1, 1, 1);
	defaultGrid.attach(denomEntry, 3, 1, 3, 1);
	defaultGrid.attach(submitButton, 0, 2, 1, 1);
	myWindow.add(defaultGrid);

	// Show everything
	modeLabel.show();
	numEntry.show();
	denomEntry.show();
	submitButton.show();
	fracLabel.show();
	slashLabel.show();
	defaultGrid.show();

	// Start main loop
	return app->run(myWindow);
}

// Increment/Decrement file functions
void incrementf()
{
	FILE* tsf=fopen("/tmp/.timeskew","r");
	if (tsf)
	{
		int num; int denom;
		fscanf(tsf, "%i %i", &num, &denom);
		fclose(tsf);
		num=(int)((float)num*1.5);
		tsf=fopen("/tmp/.timeskew","w");
		fprintf(tsf, "%i %i", num, denom);
		fclose(tsf);
		printf("%i\n", num);
	}
}

void decrementf()
{
	FILE* tsf=fopen("/tmp/.timeskew","r");
	if (tsf)
	{
		int num; int denom;
		fscanf(tsf, "%i %i", &num, &denom);
		fclose(tsf);
		num=(int)((float)num/1.5);
		if (num==0) { return; }
		tsf=fopen("/tmp/.timeskew","w");
		fprintf(tsf, "%i %i", num, denom);
		fclose(tsf);
		printf("%i\n", num);
	}
}