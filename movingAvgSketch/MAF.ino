// Initializes filter struct
void initFilter() {
  filter.total = 0;
  for (int i = 0; i < MAF_SIZE; i++) {
    filter.arr[i] = 0;
  }
  filter.index = 0;
}

// Updates MAF with a new value
void updateFilter(float newValue) {
  filter.total -= filter.arr[filter.index];
  filter.arr[filter.index] = newValue;
  filter.total += filter.arr[filter.index];
  filter.index = (filter.index + 1) % MAF_SIZE;
}

// Returns current average of filter as output
float getAve() {
  return filter.total / MAF_SIZE; // input for second derivative function
}
