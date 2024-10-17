#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;


#include <string.h>

void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
            }
        }
}

void    add_pack(package pack, post_office *office) {
    office->packages = (package *)realloc(office->packages, (office->packages_count + 1) * sizeof(package));
    office->packages[office->packages_count].id = pack.id;
    office->packages[office->packages_count].weight = pack.weight;
    office->packages_count++;
}

void    remove_pack(post_office *office, int index) {
    
    for ( ; index < office->packages_count - 1 ; index++)
    {
        office->packages[index].id = office->packages[index + 1].id;
        office->packages[index].weight = office->packages[index + 1].weight;
    }
    office->packages_count--;

    office->packages = (package *)realloc(office->packages, (office->packages_count) * sizeof(package));
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    for (int i = 0; i < source->offices[source_office_index].packages_count; i++) {
        if (source->offices[source_office_index].packages[i].weight >= target->offices[target_office_index].min_weight && source->offices[source_office_index].packages[i].weight <= target->offices[target_office_index].max_weight) {
            add_pack(source->offices[source_office_index].packages[i], &target->offices[target_office_index]);
            remove_pack(&source->offices[source_office_index], i);
            i -= 1;
        }
    }
}

town town_with_most_packages(town* towns, int towns_count) {
    town    ret;
    int     pack = 0;

    for (int i = 0; i < towns_count; i++) {
        int sum = 0;
        for (int j = 0; j < towns[i].offices_count; j++)
            sum += towns[i].offices[j].packages_count;
        if (sum > pack) {
            pack = sum;
            ret = towns[i];
        }

    }
    return ret;
}

town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++)
        if (!strcmp(towns[i].name, name))
            return towns + i;
    return NULL;
}



int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}