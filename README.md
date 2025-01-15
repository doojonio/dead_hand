
# The Dead Hand

A program to execute things (protocols) with a specified delay unless got a delay prolongation signal
with in-memory encryted entities.

# Protocols

Things to execute.

## dmsg

Delayed Message. Sends a message with specified delay and repeats with specified period.
Linked entities: messages, attachments, recipient_groups, channels


# Entities

Entities to manipulate by protocols.

## messages

1. Email Messages

## attachments

Attachments are common for all types of channels and messages.

## recipient_groups

1. Email Recipient Group

## channels

1. Email Channel


# Example config

```json
{
    "version": "1",
    "channels": {
        "ch_email": {
            "type": "email",
            "host": "smtp.google.com",
            "port": 465,
            "email": "send_by@gmail.com",
            "auth_login": "<secret>",
            "auth_pass": "<secret>",
            "timeout_ms": 30000
        }
    },
    "recipients_groups": {
        "rg_email": {
            "type": "email",
            "name": "tripleS",
            "emails": [
                "s1@pm.me",
                "s2@pm.me",
                "s3@pm.me",
                // ...
                "s24@pm.me"
            ]
        },
        "rg_me": {
            "type": "email",
            "name": "Me",
            "emails": [
                "my_email@example.org",
            ]
        }
    },
    "attachments": {
        "pic": {
            "mime": "image/jpeg",
            "url": "file:///samples/pic.jpg",
            "name": "name_in_email.jpg"
        },
        "test_pic": {
            "mime": "image/jpeg",
            "b64_content": "SGVsbG8gd29ybGQh...",
            "name": "test_pic.jpg"
        },
    },
    "messages": {
        "msg_email": {
            "type": "email",
            "channel": "ch_email",
            "recipient_group": "rg_email",
            "subject": "Check it lol",
            "body": "Hello, World!",
            "attachments": ["pic"]
        },
        "service_message": {
            "type": "email",
            "channel": "ch_email",
            "recipient_group": "rg_me",
            "subject": "Message to check if it works",
            "body": "Body messagbe with attachments",
            "attachments": ["test_pic"]
        }
    },
    "protocols": {
        "all_in": {
            "type": "dmsg",
            "delay": 255,
            "repeat": 7,
            "prolong": 90,
            "prolong_secret": "<secret>",
            "messages": [
                "msg_email"
            ]
        },
        "checker": {
            "type": "dmsg",
            "delay": 0,
            "repeat": 1,
            "prolong": 0,
            "prolong_secret": "<secret>",
            "messages": [
                "service_message"
            ]
        }
    }
}

```

