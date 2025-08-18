#pragma once

struct Customer;

typedef struct {
	void(*init)(struct Customer*);
	void(*print)(struct Customer*);
	void(*freedata)(struct Customer*);
	float(*discount)(struct Customer*);
}customerVTable;

