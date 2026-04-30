/************************************************************************************
  If not stated otherwise in this file or this component's Licenses.txt file the
  following copyright and licenses apply:

  Copyright 2024 RDK Management

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
**************************************************************************/

#include "ansc_platform.h"

/**
 * AnscQueueInitializeHeader - Initialize a queue header
 * From common-library/source/cosa/include/ansc_wrapper_api.h
 *
 * @param QueueHead: Pointer to the queue header to initialize
 */
void
AnscQueueInitializeHeader
    (
        PQUEUE_HEADER               QueueHead
    )
{
    QueueHead->Next.Next = NULL;
    QueueHead->Last.Next = NULL;
    QueueHead->Depth     = 0;
}

/**
 * AnscQueuePopEntry - Remove and return the first entry from a queue
 *
 * @param QueueHead: Pointer to the queue header
 *
 * @return: Pointer to the first entry, or NULL if queue is empty
 */
PSINGLE_LINK_ENTRY
AnscQueuePopEntry
    (
        PQUEUE_HEADER               QueueHead
    )
{
    PSINGLE_LINK_ENTRY              FirstEntry;

    FirstEntry = (QueueHead)->Next.Next;
    if ( FirstEntry == NULL )
    {
        return NULL;
    }
    QueueHead->Next.Next = FirstEntry->Next;
    QueueHead->Depth--;
    if ( FirstEntry->Next == NULL)
    {
        QueueHead->Last.Next = NULL;
    }
    return  FirstEntry;
}

/**
 * AnscQueuePushEntry - Add an entry to the end of a queue
 *
 * @param QueueHead: Pointer to the queue header
 * @param Entry: The entry to add
 */
void
AnscQueuePushEntry
    (
        PQUEUE_HEADER               QueueHead,
        PSINGLE_LINK_ENTRY          Entry
    )
{
    Entry->Next = NULL;

    if ( QueueHead->Next.Next == NULL )
    {
        QueueHead->Next.Next = Entry;
        QueueHead->Last.Next = Entry;
    }
    else
    {
        QueueHead->Last.Next->Next = Entry;
        QueueHead->Last.Next       = Entry;
    }

    QueueHead->Depth++;
}
