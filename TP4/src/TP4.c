#include <rtems.h>

/* functions */

rtems_task Init(rtems_task_argument argument);

rtems_task task_1_acquisition(rtems_task_argument unused);

void timer_1_entry(rtems_id timer_id, void* timer_input);

rtems_task task_2_traitement(rtems_task_argument unused);


/* global variables */

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

extern rtems_id   Task_id[ 4 ];         /* array of task ids */
extern rtems_name Task_name[ 4 ];       /* array of task names */


/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_INIT
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER
#define CONFIGURE_MICROSECONDS_PER_TICK 10000
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES 10
#define CONFIGURE_MAXIMUM_SEMAPHORES 1024
#define CONFIGURE_MAXIMUM_TIMERS 5
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS             4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_EXTRA_TASK_STACKS         (3 * RTEMS_MINIMUM_STACK_SIZE)

#include <rtems/confdefs.h>

static inline uint32_t get_ticks_per_second( void )
{
  rtems_interval ticks_per_second;
  (void) rtems_clock_get( RTEMS_CLOCK_GET_TICKS_PER_SECOND, &ticks_per_second );

  return ticks_per_second;
}


#include <stdio.h>
#include <stdlib.h>



#define MESSAGE_QUEUE_COUNT	4
/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

rtems_id   Task_id[ 4 ];         /* array of task ids */
rtems_name Task_name[ 4 ];       /* array of task names */

rtems_id   timer_id_1;         /* timer id */

rtems_id message_queue_id_1;

rtems_id message_queue_id_2;

rtems_task Init(rtems_task_argument argument)
{
  rtems_status_code status;

  Task_name[ 1 ] = rtems_build_name( 'T', 'S', 'K', '1' );
  Task_name[ 2 ] = rtems_build_name( 'T', 'S', 'K', '2' );

  status = rtems_task_create(
    Task_name[ 1 ], 1, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 1 ]);

  status = rtems_task_create(
    Task_name[ 2 ], 1, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 2 ]);

  status = rtems_timer_create(rtems_build_name( 'T', 'I', 'M', '1' ), &timer_id_1);
  status = rtems_timer_fire_after(timer_id_1, 50, timer_1_entry, 0);//50 = 500ms => demi-seconde

  status = rtems_message_queue_create(rtems_build_name('M','S','Q', '1'), MESSAGE_QUEUE_COUNT, CONFIGURE_MAXIMUM_MESSAGE_QUEUES,
  		  RTEMS_LOCAL | RTEMS_PRIORITY, &message_queue_id_1);

  status = rtems_task_start( Task_id[ 1 ], task_1_acquisition, 1 );

  //status = rtems_task_start( Task_id[ 2 ], task_2_traitement, 1 );

  status = rtems_task_delete( RTEMS_SELF );
}
#include <stdio.h>
#include <stdlib.h>
#include <asm-leon/irq.h>
#include <asm-leon/timer.h>

#include "global.h"
#include "windows-producer.h"


#define BUFFER_SIZE 36*100

#define BUFFER_TIMER 1

#define FLUX_LENGTH 10

uint32_t buffer[BUFFER_TIMER];

float img_buffer[BUFFER_SIZE];

uint32_t breakPoint(uint32_t time)
{
	uint32_t static test_count = 0;
	return test_count++;
}

rtems_task task_1_acquisition(rtems_task_argument unused)
{

	uint32_t time;
	size_t	size;
	rtems_status_code status;
	Windows_producer wp;
	//float* img_buffer = get_mask(Windows_producer* wp, uint32_t i);

	init(&wp, img_buffer, 100);

	while (1)
	{
		produce_images(&wp);
		rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &time);
		breakPoint(time);
		//rtems_task_wake_after(50);//50 tics = 500 ms
		status = rtems_message_queue_receive(message_queue_id_1, img_buffer, &size, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
	}
}
/*
 * fonction timer
 */
void timer_1_entry(rtems_id timer_id, void* timer_input)
{
	rtems_status_code status;

	status = rtems_message_queue_send(message_queue_id_1, buffer, sizeof(uint32_t));
	status = rtems_timer_fire_after(timer_id_1, 50, timer_1_entry, 0);//10 = 100ms

}

/* Fonction de calcul de la photom�trie par masque pond�r� */
float calcul_photometrie_pondere(float * fenetre, float * masque)
{
	float poids = 0;
	int size = 36;
	int i;

	for(i=0;i<size;i++){
		poids += fenetre[i] * masque[i];
	}

	return poids;
}

typedef struct flux{

	uint32_t id_windows;
	uint32_t id_first_aquisition;///< valeur du compteur d'aquisition de mesures[0]
	float mesures[FLUX_LENGTH];

}flux;

rtems_task task_2_traitement(rtems_task_argument unused)
{
	uint32_t buffer[BUFFER_TIMER];
	rtems_status_code status;

	flux flux;
	//doit utiliser img_buffer de l'aquisition

	float img_buffer[BUFFER_SIZE];

}

