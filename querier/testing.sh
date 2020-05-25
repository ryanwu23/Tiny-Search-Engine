#!/bin/bash
echo Testing wiki with fuzzquery with 100 inputs
echo NOTE: need to have wiki directory created by crawler and output file created by indexer ../crawler/wiki ../indexer/output
./fuzzquery ../indexer/output  100 0 | ./querier ../crawler/wiki ../indexer/output
