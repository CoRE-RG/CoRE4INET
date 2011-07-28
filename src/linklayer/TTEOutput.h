#ifndef __INET_TTEOUTPUT_H
#define __INET_TTEOUTPUT_H

#include <omnetpp.h>
#include <csimplemodule.h>
#include <INETDefs.h>
#include <IPassiveQueue.h>
#include <QueueWithQoS.h>
#include <EtherFrame_m.h>

namespace TTEthernetModel
{
	class INET_API TTEOutput : public cSimpleModule, public IPassiveQueue
	{
	public:
		TTEOutput();
		virtual ~TTEOutput();

	private:
		int framesRequested;
		cQueue ttQueue;
		cQueue beQueue;
		cQueue rcQueue;

	protected:
		/** @name Redefined cSimpleModule member functions. */
		//@{
		virtual void initialize();

		/**
		 * Calls handleIncomingFrame() for frames arrived from outside,
		 * and processFrame() for self messages.
		 */
		virtual void handleMessage(cMessage *msg);

		/**
		 * Writes statistics.
		 */
		virtual void finish();
		//@}

		/**
		 * The queue should send a packet whenever this method is invoked.
		 * If the queue is currently empty, it should send a packet when
		 * when one becomes available.
		 */
		virtual void requestPacket();

		/**
		 * Returns number of pending requests.
		 */
		virtual int getNumPendingRequests();

		/**
		 * Return true when queue is empty, otherwise return false.
		 */
		virtual bool isEmpty();

		/**
		 * Clear all queued packets and stored requests.
		 */
		virtual void clear();
	};
}

#endif



