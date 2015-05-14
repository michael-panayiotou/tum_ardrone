## Εγκατάσταση tum_ardrone
###Προαπαιτούμενα
- Λειτουργικό Σύστημα: Ubuntu 14.04 (προτεινόμενο) ή Ubuntu 13.10
- ROS έκδοση Indigo
## Οδηγίες εγκατάστασης tum_ardrone
- Ανοίξτε ένα νέο τερματικό (terminal window) και εκτελέστε την ακόλουθη εντολή για να αλλάξετε το τρέχων directory σας στον φάκελο src του catkin workspace:
###cd ~/catkin_ws/src
- Ακολούθως κάνουμε clone τον κώδικα από το repository του tum_ardrone στο catkin workspace :
###git clone https://github.com/tum-vision/tum_ardrone.git -b hydro-devel
- Επιστρέφουμε στο catkin workspace.
###cd ~/catkin_ws
- Εγκαθιστούμε τις απαιτούμενες εξαρτήσεις για το tum_ardrone με την εντολή:
###rosdep install tum_ardrone
- Κάνουμε compile το πακέτο με την εντολή:
###catkin_make
