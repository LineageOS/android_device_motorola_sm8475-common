
CREATE TABLE IF NOT EXISTS qcril_properties_table (property TEXT, def_val TEXT, value TEXT, PRIMARY KEY(property));
UPDATE qcril_properties_table set value='38' where property='qcrildb_version';

DELETE FROM qcril_emergency_source_mcc_mnc_table where MCC = '262' AND MNC = '03' AND NUMBER = '110';
DELETE FROM qcril_emergency_source_mcc_mnc_table where MCC = '262' AND MNC = '07' AND NUMBER = '110';

