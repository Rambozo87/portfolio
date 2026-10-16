#include "read_hid.h"

#include <iostream>

read_hid::read_hid(int vendor_id, int product_id) {
  if (hid_init() != 0)
    return;
  handle = hid_open(vendor_id, product_id, nullptr);
  if (!handle) {
    std::cerr << "Unable to open device (VID/PID or permissions)\n";
    hid_exit();
  }
}

read_hid::~read_hid() {
  if (handle)
    hid_close(handle);
  hid_exit();
}

bool read_hid::is_open() const { return handle != nullptr; }

unsigned char *read_hid::read() {
  if (!handle || hid_read(handle, buffer, sizeof(buffer)) <= 0)
    return nullptr;
  return buffer;
}
