// --------------------------------------------------------
//
// This file is to configure the configurable settings.
// Load this file before script.js file at gmap.html.
//
// --------------------------------------------------------

// -- Output Settings -------------------------------------
// Show metric values
Metric = false; // true or false

// -- Map settings ----------------------------------------
// The Latitude and Longitude in decimal format
CONST_CENTERLAT = 40.218659;
CONST_CENTERLON = -76.877964;
// The google maps zoom level, 0 - 16, lower is further out
CONST_ZOOMLVL   = 5;

// -- Marker settings -------------------------------------
// The default marker color
MarkerColor	  = "rgb(127, 127, 127)";
SelectedColor = "rgb(225, 225, 225)";
StaleColor = "rgb(190, 190, 190)";

// -- Site Settings ---------------------------------------
SiteShow    = true; // true or false
// The Latitude and Longitude in decimal format
SiteLat     = 40.218659;
SiteLon     = -76.877964;

SiteCircles = true; // true or false (Only shown if SiteShow is true)
// In nautical miles or km (depending settings value 'Metric')
SiteCirclesDistances = new Array(25,50,100,150);

