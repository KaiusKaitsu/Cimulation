//This is my simulation program loosely based on my larger school project FollowTheLeader simulation.
//Quite basic as memory faults run rampant

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

// Simulant structure to represent simulants
typedef struct {
    double x;
    double y;
    double heading;
} Simulant;

// Simulation parameters
#define NUM_SIMULANTS 10
#define MAP_X 800
#define MAP_Y 800
#define SPEED 1

//Simulants live in this array
Simulant simulants[NUM_SIMULANTS];

void updateDir(Simulant sim){
	sim.heading += ((double)rand() / RAND_MAX -0.5)*0.2;
}


void updatePos(Simulant sim) {
	sim.x += SPEED * cos(sim.heading);
	sim.x += SPEED * sin(sim.heading);
	//border logic
	if (sim.x<0) sim.x = MAP_X;
	if (sim.x>MAP_X) sim.x = 0;
	if (sim.y<0) sim.y = MAP_Y;
	if (sim.y>MAP_Y) sim.y = 0;
}

//update all simulants
void update() {
	for (int i = 0; i < NUM_SIMULANTS; ++i) {
	updateDir(simulants[i]);
	updatePos(simulants[i]);
	}
}

//Visual logic is fond here. First the draw function
gboolean draw(GtkWidget* widget, cairo_t* cr, gpointer user_data) {
    // paitn black background
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    // Set color to red
    cairo_set_source_rgb(cr, 1, 0, 0);

    // Draw each Simulant as a red circle
    for (int i = 0; i < NUM_SIMULANTS; ++i) {
        cairo_arc(cr, simulants[i].x, simulants[i].y, 10, 0, 2 * G_PI);
        cairo_fill(cr);
    }

    return FALSE;
}

void initialize_simulants() {
    // Initialize Simulants with random positions
    for (int i = 0; i < NUM_SIMULANTS; ++i) {
        simulants[i].x = rand() % (MAP_X-50) + 50; 
        simulants[i].y = rand() % (MAP_Y-50) + 50;
	simulants[i].heading = ((double)rand() / RAND_MAX) * 2 * G_PI;
    }
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simulants Drawing");
    gtk_window_set_default_size(GTK_WINDOW(window), MAP_X, MAP_Y);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create drawing area
    GtkWidget* drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, MAP_X, MAP_Y);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Initialize Simulants
    initialize_simulants();

    // Connect draw signal and add timer to update every 100ms
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw), NULL);
    g_timeout_add(100,(GSourceFunc)update, NULL);

    // Show all and start 
    gtk_widget_show_all(window);
    gtk_main();
	
    return 0;
}

