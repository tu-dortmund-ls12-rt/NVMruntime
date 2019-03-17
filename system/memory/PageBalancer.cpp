#include "PageBalancer.h"

template class RBTree<phys_page_handle>;
template class Node_Comparator<phys_page_handle>;
template <>
int Node_Comparator<phys_page_handle>::compare(phys_page_handle node1,
                                               phys_page_handle node2) {
    if (node2.access_count != node1.access_count) {
        return node1.access_count - node2.access_count;
    }
    return node1.phys_address -
           node2.phys_address;  // Just to keep an absolute ordner in the tree
}
template <>
bool Node_Comparator<phys_page_handle>::equals(phys_page_handle node1,
                                               phys_page_handle node2) {
    return node1.access_count == node2.access_count &&
           node1.phys_address == node2.phys_address;
}