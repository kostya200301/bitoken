CREATE TABLE IF NOT EXISTS reKeys (
                                     id UUID PRIMARY KEY,
                                     sender_id UUID,
                                     receiver_id UUID,
                                     sender_key_version int,
                                     receiver_key_version int,
                                     created_at TIMESTAMP
) WITH default_time_to_live = 0;