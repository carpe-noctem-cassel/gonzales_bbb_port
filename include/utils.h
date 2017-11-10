#ifndef UTILS_H
#define UTILS_H

/**
 * string hash function used by the udp proxy to identify the ros topic
 * the message is sent for
 */
constexpr uint32_t
topic_hash(const char* s, const unsigned seed = 0) {
	unsigned int hash = seed;
	while (*s) {
		hash = hash * 101 + *s++;
	}
	return hash;
}

#endif // UTILS_H
