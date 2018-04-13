#include "logging.h"

extern Controlling::EposCan* ep;
extern gonzales_state gonz_state;

// logData logs the motion state to the given file
void logData(FILE *file) {
	fprintf(file,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%f\n",
		gonz_state.currentPosition.angle,gonz_state.currentPosition.x,gonz_state.currentPosition.y,
		gonz_state.actualMotion.x,gonz_state.actualMotion.y,gonz_state.actualMotion.rotation,
		gonz_state.currentMotionGoal.x,gonz_state.currentMotionGoal.y,gonz_state.currentMotionGoal.rotation,
		ep->ActualRPM(0),ep->ActualRPM(1),ep->ActualRPM(2),ep->ActualRPM(3),
		ep->DemandRPM(0),ep->DemandRPM(1),ep->DemandRPM(2),ep->DemandRPM(3),
		ep->ActualCurrent(0),ep->ActualCurrent(1),ep->ActualCurrent(2),ep->ActualCurrent(3),
		gonz_state.currentSlip
	);
}
