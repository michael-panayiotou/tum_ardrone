

## Εγκατάσταση tum_ardrone

### Προαπαιτούμενα
- Λειτουργικό Σύστημα: Ubuntu 14.04 (προτεινόμενο) ή Ubuntu 13.10
- ROS έκδοση Indigo

## Οδηγίες εγκατάστασης tum_ardrone
- Ανοίξτε ένα νέο τερματικό (terminal window) και εκτελέστε την ακόλουθη εντολή για να αλλάξετε το τρέχων directory σας στον φάκελο src του catkin workspace:
``` bash
cd ~/catkin_ws/src
```
- Ακολούθως κάνουμε clone τον κώδικα από το repository του tum_ardrone στο catkin workspace :
``` bash
git clone https://github.com/michael-panayiotou/tum_ardrone.git -b indigo-devel
```
- Επιστρέφουμε στο catkin workspace.
``` bash
cd ~/catkin_ws
```
- Εγκαθιστούμε τις απαιτούμενες εξαρτήσεις για το tum_ardrone με την εντολή:
``` bash
rosdep install tum_ardrone
```
- Κάνουμε compile το πακέτο με την εντολή:
``` bash
catkin_make
```
