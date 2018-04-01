#include "private/private.h"

ListVtable List = {

    // Construction/destruction
    .new        = &new_List,
    .init       = &init_List,
    .del        = &del_List,
    
    // Methods
    .concat     = &concat_List,
    
    // Object interface
    .equals     = &equals_List,
    
    // Container interface
    .size       = &size_List,
    .clear      = &clear_List,
    
    // Stack interface
    .push       = &push_List,
    .pushes     = &pushes_List,
    .pop        = &pop_List,
    .back       = &back_List,
    .extend     = &extend_List,
    
    // Accessor interface
    .getitem    = &getitem_List,
    .setitem    = &setitem_List,
    .at         = &at_List,
    .set        = &set_List,
    .slice      = &slice_List
};
